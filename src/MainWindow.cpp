#include "../include/MainWindow.hpp"
#include "../include/PersonagemFactory.hpp"
#include "../include/GerenciadorJogo.hpp"
#include "../include/Mago.hpp"
#include "../include/Guerreiro.hpp"
#include "../include/Exceptions.hpp"

#include <QMessageBox>
#include <QFormLayout>
#include <QInputDialog>
#include <QDebug>
#include <QSplitter>
#include <fstream>

using namespace RpgGame;

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), emCombate(false), streamRedirector(nullptr) {
    
    setWindowTitle("RPG Manager - UTFPR");
    resize(1000, 650);

    // Aplicar Style Sheet Sleek Dark Mode
    setStyleSheet(
        "QMainWindow { background-color: #1e1e24; }"
        "QGroupBox { border: 2px solid #3a3a43; border-radius: 8px; margin-top: 15px; background-color: #25252d; color: #e0e0e6; font-weight: bold; }"
        "QGroupBox::title { subcontrol-origin: margin; subcontrol-position: top center; padding: 2px 15px; background-color: #3a3a43; border-radius: 4px; color: #00ffcc; }"
        "QLabel { color: #e0e0e6; font-size: 13px; font-weight: 500; }"
        "QPushButton { background: qlineargradient(x1:0, y1:0, x2:1, y2:1, stop:0 #4b5563, stop:1 #374151); border: 1px solid #1f2937; border-radius: 6px; color: #ffffff; padding: 8px 16px; font-weight: bold; }"
        "QPushButton:hover { background: qlineargradient(x1:0, y1:0, x2:1, y2:1, stop:0 #6b7280, stop:1 #4b5563); border-color: #00ffcc; }"
        "QPushButton:disabled { background: #1c1c22; color: #666; border: 1px solid #2d2d35; }"
        "QProgressBar { border: 1px solid #3a3a43; border-radius: 5px; text-align: center; color: #ffffff; font-weight: bold; background-color: #111115; }"
        "QProgressBar::chunk { background-color: #00ffcc; width: 10px; }"
        "QListWidget { background-color: #15151a; border: 1px solid #3a3a43; border-radius: 6px; color: #e0e0e6; padding: 5px; }"
        "QListWidget::item:selected { background-color: #00ffcc; color: #111115; font-weight: bold; border-radius: 4px; }"
        "QTextBrowser { background-color: #111115; border: 1px solid #3a3a43; border-radius: 6px; color: #a0ff80; font-family: 'Courier New', Courier, monospace; font-size: 12px; }"
        "QComboBox { background-color: #000000; border: 1px solid #3a3a43; border-radius: 6px; color: #e0e0e6; padding: 5px; min-width: 100px; }"
        "QComboBox QAbstractItemView { background-color: #000000; color: #e0e0e6; selection-background-color: #00ffcc; selection-color: #111115; }"
        "QLineEdit { background-color: #15151a; border: 1px solid #3a3a43; border-radius: 6px; color: #e0e0e6; padding: 6px; }"
    );

    // Widget central e layout
    QWidget* centralWidget = new QWidget(this);
    setCentralWidget(centralWidget);
    QHBoxLayout* mainLayout = new QHBoxLayout(centralWidget);

    // Divisor para painéis ajustáveis
    QSplitter* splitter = new QSplitter(Qt::Horizontal, centralWidget);
    mainLayout->addWidget(splitter);

    // --- PAINEL ESQUERDO (Status do Herói, Equipamentos e Inventário) ---
    QWidget* leftWidget = new QWidget(splitter);
    QVBoxLayout* leftLayout = new QVBoxLayout(leftWidget);

    // Ficha e Status
    QGroupBox* grpHeroi = new QGroupBox("Ficha do Herói", leftWidget);
    QGridLayout* gridHeroi = new QGridLayout(grpHeroi);
    lblNome = new QLabel("Nome: -", grpHeroi);
    lblClasseRaca = new QLabel("Classe/Raça: -", grpHeroi);
    lblNivelXP = new QLabel("Nível: - | XP: -", grpHeroi);
    
    QLabel* lblVidBar = new QLabel("Vida:", grpHeroi);
    barVida = new QProgressBar(grpHeroi);
    barVida->setStyleSheet("QProgressBar::chunk { background: qlineargradient(x1:0, y1:0, x2:1, y2:0, stop:0 #ff4e50, stop:1 #f9d423); }");
    
    QLabel* lblNrgBar = new QLabel("Recurso:", grpHeroi);
    barEnergia = new QProgressBar(grpHeroi);
    barEnergia->setStyleSheet("QProgressBar::chunk { background: qlineargradient(x1:0, y1:0, x2:1, y2:0, stop:0 #00c6ff, stop:1 #0072ff); }");

    gridHeroi->addWidget(lblNome, 0, 0, 1, 2);
    gridHeroi->addWidget(lblClasseRaca, 1, 0, 1, 2);
    gridHeroi->addWidget(lblNivelXP, 2, 0, 1, 2);
    gridHeroi->addWidget(lblVidBar, 3, 0);
    gridHeroi->addWidget(barVida, 3, 1);
    gridHeroi->addWidget(lblNrgBar, 4, 0);
    gridHeroi->addWidget(barEnergia, 4, 1);
    leftLayout->addWidget(grpHeroi);

    // Equipados
    QGroupBox* grpEquipados = new QGroupBox("Equipamentos Equipados", leftWidget);
    QVBoxLayout* vboxEquipados = new QVBoxLayout(grpEquipados);
    listEquipados = new QListWidget(grpEquipados);
    vboxEquipados->addWidget(listEquipados);
    btnDesequiparItem = new QPushButton("Desequipar", grpEquipados);
    vboxEquipados->addWidget(btnDesequiparItem);
    leftLayout->addWidget(grpEquipados);

    // Inventário
    QGroupBox* grpInventario = new QGroupBox("Inventário", leftWidget);
    QVBoxLayout* vboxInventario = new QVBoxLayout(grpInventario);
    listInventario = new QListWidget(grpInventario);
    vboxInventario->addWidget(listInventario);

    QHBoxLayout* hboxInvButtons = new QHBoxLayout();
    btnUsarItem = new QPushButton("Usar / Consumir", grpInventario);
    btnEquiparItem = new QPushButton("Equipar", grpInventario);
    hboxInvButtons->addWidget(btnUsarItem);
    hboxInvButtons->addWidget(btnEquiparItem);
    vboxInventario->addLayout(hboxInvButtons);
    leftLayout->addWidget(grpInventario);

    // Ações do Jogo
    QHBoxLayout* hboxGlobalButtons = new QHBoxLayout();
    btnSalvar = new QPushButton("Salvar Jogo", leftWidget);
    hboxGlobalButtons->addWidget(btnSalvar);
    leftLayout->addLayout(hboxGlobalButtons);

    splitter->addWidget(leftWidget);

    // --- PAINEL DIREITO (Arena de Combate e Logs) ---
    QWidget* rightWidget = new QWidget(splitter);
    QVBoxLayout* rightLayout = new QVBoxLayout(rightWidget);

    // Arena de Batalha
    grpArena = new QGroupBox("Arena de Batalha", rightWidget);
    QVBoxLayout* vboxArena = new QVBoxLayout(grpArena);
    
    lblMonstroStatus = new QLabel("Nenhum inimigo ativo", grpArena);
    vboxArena->addWidget(lblMonstroStatus);
    
    barVidaMonstro = new QProgressBar(grpArena);
    barVidaMonstro->setStyleSheet("QProgressBar::chunk { background-color: #ff3333; }");
    barVidaMonstro->setValue(0);
    barVidaMonstro->setEnabled(false);
    vboxArena->addWidget(barVidaMonstro);

    QHBoxLayout* hboxArenaActions = new QHBoxLayout();
    btnIniciarArena = new QPushButton("Iniciar Arena", grpArena);
    btnAtaqueBasico = new QPushButton("Ataque Básico", grpArena);
    comboHabilidades = new QComboBox(grpArena);
    btnUsarHabilidade = new QPushButton("Usar Skill", grpArena);

    hboxArenaActions->addWidget(btnIniciarArena);
    hboxArenaActions->addWidget(btnAtaqueBasico);
    hboxArenaActions->addWidget(comboHabilidades);
    hboxArenaActions->addWidget(btnUsarHabilidade);
    vboxArena->addLayout(hboxArenaActions);
    rightLayout->addWidget(grpArena);

    // Logs
    QGroupBox* grpLogs = new QGroupBox("Logs de Ações", rightWidget);
    QVBoxLayout* vboxLogs = new QVBoxLayout(grpLogs);
    textLogs = new QTextBrowser(grpLogs);
    vboxLogs->addWidget(textLogs);
    rightLayout->addWidget(grpLogs);

    splitter->addWidget(rightWidget);

    // Estado inicial de botões
    btnUsarItem->setEnabled(false);
    btnEquiparItem->setEnabled(false);
    btnDesequiparItem->setEnabled(false);
    btnAtaqueBasico->setEnabled(false);
    btnUsarHabilidade->setEnabled(false);
    comboHabilidades->setEnabled(false);

    // Conectar eventos
    connect(listInventario, &QListWidget::itemSelectionChanged, this, &MainWindow::onItemSelected);
    connect(listEquipados, &QListWidget::itemSelectionChanged, this, &MainWindow::onEquipadoSelected);
    connect(btnUsarItem, &QPushButton::clicked, this, &MainWindow::onUsarItem);
    connect(btnEquiparItem, &QPushButton::clicked, this, &MainWindow::onEquiparItem);
    connect(btnDesequiparItem, &QPushButton::clicked, this, &MainWindow::onDesequiparItem);
    connect(btnIniciarArena, &QPushButton::clicked, this, &MainWindow::onIniciarArena);
    connect(btnAtaqueBasico, &QPushButton::clicked, this, &MainWindow::onAtaqueBasico);
    connect(btnUsarHabilidade, &QPushButton::clicked, this, &MainWindow::onUsarHabilidade);
    connect(btnSalvar, &QPushButton::clicked, this, &MainWindow::onSalvarJogo);

    // Redirecionador do std::cout
    streamRedirector = new QDebugStream(std::cout, textLogs);

    // Registrar no Subject como Observer
    GerenciadorJogo::get_instancia().registrarObserver(this);
}

MainWindow::~MainWindow() {
    delete streamRedirector;
    GerenciadorJogo::get_instancia().removerObserver(this);
}

void MainWindow::aoAcontecerEvento(const std::string& log) {
    logarInfo(QString::fromStdString(log));
}

bool MainWindow::mostrarWelcomeDialog() {
    QDialog welcomeDialog(this);
    welcomeDialog.setWindowTitle("RPG Manager - Inicialização");
    welcomeDialog.resize(350, 200);
    welcomeDialog.setStyleSheet(
        "QDialog { background-color: #25252d; }"
        "QLabel { color: #e0e0e6; font-size: 14px; font-weight: bold; }"
        "QPushButton { background-color: #4b5563; border-radius: 6px; color: #ffffff; padding: 10px; font-weight: bold; }"
        "QPushButton:hover { background-color: #00ffcc; color: #111115; }"
        "QComboBox { background-color: #000000; border: 1px solid #3a3a43; border-radius: 6px; color: #e0e0e6; padding: 5px; min-width: 100px; }"
        "QComboBox QAbstractItemView { background-color: #000000; color: #e0e0e6; selection-background-color: #00ffcc; selection-color: #111115; }"
        "QLineEdit { background-color: #15151a; border: 1px solid #3a3a43; border-radius: 6px; color: #e0e0e6; padding: 6px; }"
    );

    QVBoxLayout* layout = new QVBoxLayout(&welcomeDialog);
    QLabel* title = new QLabel("BEM-VINDO AO RPG MANAGER\nSelecione uma opção:", &welcomeDialog);
    title->setAlignment(Qt::AlignCenter);
    layout->addWidget(title);

    QPushButton* btnNovo = new QPushButton("Novo Jogador", &welcomeDialog);
    QPushButton* btnCarregar = new QPushButton("Carregar Jogador", &welcomeDialog);
    layout->addWidget(btnNovo);
    layout->addWidget(btnCarregar);

    bool inicializado = false;

    connect(btnCarregar, &QPushButton::clicked, [&]() {
        std::ifstream in("savegame.txt");
        if (in.is_open()) {
            in.close();
            try {
                int prog = 0;
                auto loadedHero = Persistencia::carregarJogo("savegame.txt", prog);
                if (loadedHero) {
                    GerenciadorJogo::get_instancia().set_heroi(loadedHero);
                    GerenciadorJogo::get_instancia().set_progresso_batalha(prog);
                    inicializado = true;
                    welcomeDialog.accept();
                }
            } catch (const PersistenciaException& e) {
                QMessageBox::warning(&welcomeDialog, "Erro", e.what());
            }
        } else {
            QMessageBox::warning(&welcomeDialog, "Aviso", "Nenhum jogo salvo encontrado! Crie um Novo Jogador.");
        }
    });

    connect(btnNovo, &QPushButton::clicked, [&]() {
        // Sub-dialog de criação
        QDialog createDialog(&welcomeDialog);
        createDialog.setWindowTitle("Criar Novo Herói");
        createDialog.resize(350, 300);
        createDialog.setStyleSheet(welcomeDialog.styleSheet());

        QFormLayout* form = new QFormLayout(&createDialog);
        
        QLineEdit* editNome = new QLineEdit(&createDialog);
        QComboBox* cbRaca = new QComboBox(&createDialog);
        cbRaca->addItems({"Humano", "Elfo", "Anão", "Orc", "Dragão"});
        
        QComboBox* cbClasse = new QComboBox(&createDialog);
        cbClasse->addItems({"Guerreiro", "Mago", "Arqueiro", "Druida", "Ladrão", "Construtor de Energia", "Clérigo"});

        form->addRow("Nome do Herói:", editNome);
        form->addRow("Raça:", cbRaca);
        form->addRow("Classe:", cbClasse);

        QPushButton* btnCriar = new QPushButton("Começar Aventura", &createDialog);
        form->addRow(btnCriar);

        connect(btnCriar, &QPushButton::clicked, [&]() {
            QString nome = editNome->text().trimmed();
            if (nome.isEmpty()) {
                QMessageBox::warning(&createDialog, "Erro", "O nome do herói não pode ser vazio!");
                return;
            }

            try {
                std::string classeStr = cbClasse->currentText().toStdString();
                std::string racaStr = cbRaca->currentText().toStdString();

                // Usando a Factory de Personagem
                auto newHero = PersonagemFactory::criar_personagem(nome.toStdString(), classeStr, racaStr, 1);
                GerenciadorJogo::get_instancia().set_heroi(newHero);

                // Sobrecarga de operador + para itens e experiência iniciais
                *newHero + std::make_shared<Arma>("Espada de Aço", "Arma cortante afiada", 3.0, 10, 15);
                *newHero + std::make_shared<Pocao>("Poção de Cura", "Restaura 50 de vida", 0.5, 5, 50);
                *newHero + std::make_shared<PocaoEnergia>("Poção de Energia", "Restaura 30 de energia", 0.5, 5, 30);
                *newHero + std::make_shared<ItemEspecial>("Cristal Divino", "Restaura 25 de energia", 0.2, 20, 25);
                *newHero + 10; // Adiciona 10 XP usando operador +

                inicializado = true;
                GerenciadorJogo::get_instancia().set_progresso_batalha(0);
                createDialog.accept();
                welcomeDialog.accept();
            } catch (const RPGException& e) {
                QMessageBox::warning(&createDialog, "Erro", e.what());
                GerenciadorJogo::get_instancia().set_heroi(nullptr);
            }
        });

        createDialog.exec();
    });

    welcomeDialog.exec();
    
    if (inicializado) {
        atualizarFicha();
        atualizarInventario();
        atualizarEquipados();
        atualizarArena();
        auto heroi = GerenciadorJogo::get_instancia().get_heroi();
        logarInfo("Seja bem-vindo, " + QString::fromStdString(heroi->get_nome()) + "! Sua aventura se inicia agora.");
        return true;
    }
    return false;
}

void MainWindow::atualizarFicha() {
    auto heroi = GerenciadorJogo::get_instancia().get_heroi();
    if (!heroi) return;
    
    lblNome->setText(QString("Nome: %1").arg(QString::fromStdString(heroi->get_nome())));
    lblClasseRaca->setText(QString("Classe: %1 | Raça: %2")
        .arg(QString::fromStdString(heroi->get_classe_rpg()))
        .arg(QString::fromStdString(heroi->get_raca())));
    
    // XP e Meta
    int xp = heroi->get_experiencia();
    int metaXP = heroi->get_exp_proximo_nivel();
    lblNivelXP->setText(QString("Nível: %1 | XP: %2 / %3").arg(heroi->get_nivel()).arg(xp).arg(metaXP));

    // Barras
    barVida->setMaximum(heroi->get_pontos_vida_max());
    barVida->setValue(heroi->get_pontos_vida_atual());
    barVida->setFormat(QString("%1/%2 HP").arg(heroi->get_pontos_vida_atual()).arg(heroi->get_pontos_vida_max()));

    // Gestão do recurso de energia de acordo com a classe
    auto mago = std::dynamic_pointer_cast<Mago>(heroi);
    auto guerreiro = std::dynamic_pointer_cast<Guerreiro>(heroi);
    if (mago) {
        barEnergia->setMaximum(mago->get_mana_max());
        barEnergia->setValue(mago->get_mana_atual());
        barEnergia->setFormat(QString("%1/%2 MP").arg(mago->get_mana_atual()).arg(mago->get_mana_max()));
    } else if (guerreiro) {
        barEnergia->setMaximum(100);
        barEnergia->setValue(guerreiro->get_furia());
        barEnergia->setFormat(QString("%1/100 Fúria").arg(guerreiro->get_furia()));
    } else {
        barEnergia->setMaximum(heroi->get_energia_max());
        barEnergia->setValue(heroi->get_energia_atual());
        barEnergia->setFormat(QString("%1/%2 EP").arg(heroi->get_energia_atual()).arg(heroi->get_energia_max()));
    }
}

static QString obterEspecificacaoItem(std::shared_ptr<Item> it) {
    if (!it) return "";
    
    if (it->get_tipo() == TipoItem::Arma) {
        if (auto arma = std::dynamic_pointer_cast<Arma>(it)) {
            return QString("(+%1 dano)").arg(arma->get_dano_bonus());
        }
    } else if (it->get_tipo() == TipoItem::Armadura) {
        if (auto armadura = std::dynamic_pointer_cast<Armadura>(it)) {
            return QString("(+%1 defesa)").arg(armadura->get_defesa_bonus());
        }
    } else if (it->get_tipo() == TipoItem::Pocao) {
        if (auto pocao = std::dynamic_pointer_cast<Pocao>(it)) {
            return QString("(+%1 cura)").arg(pocao->get_cura());
        }
    } else if (it->get_tipo() == TipoItem::PocaoEnergia) {
        if (auto pe = std::dynamic_pointer_cast<PocaoEnergia>(it)) {
            return QString("(+%1 energia)").arg(pe->get_energia_restaurada());
        }
    } else if (it->get_tipo() == TipoItem::Bomba) {
        if (auto bomba = std::dynamic_pointer_cast<BombaCaseira>(it)) {
            return QString("(+%1 dano)").arg(bomba->get_dano());
        }
    } else if (it->get_tipo() == TipoItem::Especial) {
        if (auto ie = std::dynamic_pointer_cast<ItemEspecial>(it)) {
            return QString("(+%1 energia)").arg(ie->get_bonus_status());
        }
    }
    return "";
}

void MainWindow::atualizarInventario() {
    listInventario->clear();
    auto heroi = GerenciadorJogo::get_instancia().get_heroi();
    if (!heroi) return;

    Inventario& inv = heroi->get_inventario();
    for (int i = 0; i < inv.get_quantidade_itens(); ++i) {
        auto it = inv.get_item(i);
        if (it) {
            QString tipoStr = "";
            switch (it->get_tipo()) {
                case TipoItem::Arma: tipoStr = "[Arma] "; break;
                case TipoItem::Armadura: tipoStr = "[Armadura] "; break;
                case TipoItem::Pocao: tipoStr = "[Poção Vida] "; break;
                case TipoItem::PocaoEnergia: tipoStr = "[Poção Energia] "; break;
                case TipoItem::Bomba: tipoStr = "[Bomba] "; break;
                case TipoItem::Especial: tipoStr = "[Especial] "; break;
            }
            QString spec = obterEspecificacaoItem(it);
            if (!spec.isEmpty()) {
                spec = " " + spec;
            }
            listInventario->addItem(QString("%1%2%3 (%4 kg) - %5")
                .arg(tipoStr)
                .arg(QString::fromStdString(it->get_nome()))
                .arg(spec)
                .arg(it->get_peso())
                .arg(QString::fromStdString(it->get_descricao())));
        }
    }

    // Limpar seleção
    btnUsarItem->setEnabled(false);
    btnEquiparItem->setEnabled(false);
}

void MainWindow::atualizarEquipados() {
    listEquipados->clear();
    auto heroi = GerenciadorJogo::get_instancia().get_heroi();
    if (!heroi) return;

    // Arma equipada
    if (auto arma = heroi->get_arma_equipada()) {
        QString spec = obterEspecificacaoItem(arma);
        listEquipados->addItem(QString("[Arma] %1 %2")
            .arg(QString::fromStdString(arma->get_nome()))
            .arg(spec));
    } else {
        listEquipados->addItem("[Arma] Nenhuma");
    }

    // Armaduras equipadas
    const auto& armaduras = heroi->get_armaduras_equipadas();
    for (auto const& [slot, armadura] : armaduras) {
        if (armadura) {
            QString spec = obterEspecificacaoItem(armadura);
            listEquipados->addItem(QString("[%1] %2 %3")
                .arg(QString::fromStdString(slot))
                .arg(QString::fromStdString(armadura->get_nome()))
                .arg(spec));
        }
    }
    
    btnDesequiparItem->setEnabled(false);
}

void MainWindow::atualizarArena() {
    auto monstroAtual = GerenciadorJogo::get_instancia().get_monstro_atual();
    int progressoBatalha = GerenciadorJogo::get_instancia().get_progresso_batalha();
    auto heroi = GerenciadorJogo::get_instancia().get_heroi();

    if (emCombate && monstroAtual) {
        lblMonstroStatus->setText(QString("Inimigo: %1 (Nv.%2)")
            .arg(QString::fromStdString(monstroAtual->get_nome()))
            .arg(monstroAtual->get_nivel()));
        barVidaMonstro->setEnabled(true);
        barVidaMonstro->setMaximum(monstroAtual->get_pontos_vida_max());
        barVidaMonstro->setValue(monstroAtual->get_pontos_vida_atual());
        barVidaMonstro->setFormat(QString("%1/%2 HP").arg(monstroAtual->get_pontos_vida_atual()).arg(monstroAtual->get_pontos_vida_max()));
        
        btnIniciarArena->setEnabled(false);
        btnAtaqueBasico->setEnabled(true);
        comboHabilidades->setEnabled(true);
        btnUsarHabilidade->setEnabled(true);
        btnSalvar->setEnabled(false);
    } else {
        if (progressoBatalha >= 5) {
            lblMonstroStatus->setText("Arena Finalizada! O reino está salvo.");
            btnIniciarArena->setEnabled(false);
        } else {
            QString nomeProximo = "";
            switch(progressoBatalha) {
                case 0: nomeProximo = "Goblin (Nv.1)"; break;
                case 1: nomeProximo = "Orc Furioso (Nv.3)"; break;
                case 2: nomeProximo = "Lobo Mau (Nv.5)"; break;
                case 3: nomeProximo = "Gigante Malvadão (Nv.10)"; break;
                case 4: nomeProximo = "Peppa Pig (Nv.20)"; break;
            }
            lblMonstroStatus->setText(QString("Próximo desafio: %1").arg(nomeProximo));
            btnIniciarArena->setEnabled(true);
        }
        barVidaMonstro->setValue(0);
        barVidaMonstro->setEnabled(false);
        barVidaMonstro->setFormat("-");
        btnAtaqueBasico->setEnabled(false);
        comboHabilidades->setEnabled(false);
        btnUsarHabilidade->setEnabled(false);
        btnSalvar->setEnabled(true);
    }

    // Habilidades no combobox
    comboHabilidades->clear();
    if (heroi) {
        int idx = 0;
        while (true) {
            Habilidade* hab = heroi->escolher_habilidade(idx);
            if (!hab) break;
            comboHabilidades->addItem(QString("%1 %2").arg(QString::fromStdString(hab->get_nome())).arg(QString::fromStdString(hab->get_efeito_str())));
            idx++;
        }
    }
}

void MainWindow::logarInfo(const QString& msg) {
    textLogs->append("<font color='#00ffcc'><b>[SISTEMA]</b></font> " + msg);
}

void MainWindow::onItemSelected() {
    auto heroi = GerenciadorJogo::get_instancia().get_heroi();
    if (!heroi) return;

    int idx = listInventario->currentRow();
    if (idx < 0) {
        btnUsarItem->setEnabled(false);
        btnEquiparItem->setEnabled(false);
        return;
    }

    auto item = heroi->get_inventario().get_item(idx);
    if (!item) {
        btnUsarItem->setEnabled(false);
        btnEquiparItem->setEnabled(false);
        return;
    }

    if (item->get_tipo() == TipoItem::Arma || item->get_tipo() == TipoItem::Armadura) {
        btnEquiparItem->setEnabled(true);
        btnUsarItem->setEnabled(false);
    } else {
        btnEquiparItem->setEnabled(false);
        btnUsarItem->setEnabled(true);
    }
}

void MainWindow::onEquipadoSelected() {
    int idx = listEquipados->currentRow();
    if (idx < 0) {
        btnDesequiparItem->setEnabled(false);
        return;
    }

    QListWidgetItem* selected = listEquipados->item(idx);
    if (!selected) {
        btnDesequiparItem->setEnabled(false);
        return;
    }

    QString text = selected->text();
    if (text.isEmpty() || text.endsWith("Nenhuma")) {
        btnDesequiparItem->setEnabled(false);
    } else {
        btnDesequiparItem->setEnabled(true);
    }
}

void MainWindow::onUsarItem() {
    auto heroi = GerenciadorJogo::get_instancia().get_heroi();
    if (!heroi) return;

    int idx = listInventario->currentRow();
    if (idx < 0) return;

    auto item = heroi->get_inventario().get_item(idx);
    if (!item) return;

    try {
        heroi->usar_item(item->get_nome());
        
        atualizarFicha();
        atualizarInventario();
        atualizarEquipados();
        atualizarArena();
        
        if (emCombate) {
            processarTurnoMonstro();
        }
    } catch (const RPGException& e) {
        QMessageBox::warning(this, "Erro", e.what());
    }
}

void MainWindow::onEquiparItem() {
    auto heroi = GerenciadorJogo::get_instancia().get_heroi();
    if (!heroi) return;

    int idx = listInventario->currentRow();
    if (idx < 0) return;

    auto item = heroi->get_inventario().get_item(idx);
    if (!item) return;

    heroi->equipar_item(item);

    atualizarFicha();
    atualizarInventario();
    atualizarEquipados();
    atualizarArena();
}

void MainWindow::onDesequiparItem() {
    auto heroi = GerenciadorJogo::get_instancia().get_heroi();
    if (!heroi) return;

    int idx = listEquipados->currentRow();
    if (idx < 0) return;

    QListWidgetItem* selected = listEquipados->item(idx);
    if (!selected) return;

    QString text = selected->text();
    if (text.isEmpty() || text.endsWith("Nenhuma")) return;

    if (text.startsWith("[Arma]")) {
        auto arma = heroi->get_arma_equipada();
        if (arma) heroi->desequipar_item(arma->get_nome());
    } else {
        int endBracket = text.indexOf(']');
        if (endBracket > 1) {
            QString slot = text.mid(1, endBracket - 1);
            heroi->desequipar_item(slot.toStdString());
        }
    }

    atualizarFicha();
    atualizarInventario();
    atualizarEquipados();
    atualizarArena();
}

void MainWindow::onIniciarArena() {
    try {
        GerenciadorJogo::get_instancia().iniciar_desafio_arena();
        emCombate = true;
        
        atualizarFicha();
        atualizarArena();
    } catch (const RPGException& e) {
        QMessageBox::warning(this, "Erro", e.what());
    }
}

void MainWindow::onAtaqueBasico() {
    auto heroi = GerenciadorJogo::get_instancia().get_heroi();
    auto monstroAtual = GerenciadorJogo::get_instancia().get_monstro_atual();

    try {
        if (!emCombate || !monstroAtual || !monstroAtual->is_vivo()) {
            throw CombateException("Nenhum inimigo válido na arena para atacar!");
        }

        logarInfo("----------------- TURNO JOGADOR -----------------");
        heroi->atacar(*monstroAtual, 0); // 0 indica ataque básico

        atualizarFicha();
        atualizarArena();
        verificarFimDeCombate();

        if (emCombate) {
            processarTurnoMonstro();
        }
    } catch (const RPGException& e) {
        logarInfo(QString("Erro: ") + e.what());
        QMessageBox::warning(this, "Ação Inválida", e.what());
    }
}

void MainWindow::onUsarHabilidade() {
    auto heroi = GerenciadorJogo::get_instancia().get_heroi();
    auto monstroAtual = GerenciadorJogo::get_instancia().get_monstro_atual();

    try {
        if (!emCombate || !monstroAtual || !monstroAtual->is_vivo()) {
            throw CombateException("Nenhum inimigo válido na arena para atacar!");
        }

        int idx = comboHabilidades->currentIndex();
        logarInfo("----------------- TURNO JOGADOR -----------------");
        heroi->atacar(*monstroAtual, idx + 1); // index + 1 indica habilidade correspondente

        atualizarFicha();
        atualizarArena();
        verificarFimDeCombate();

        if (emCombate) {
            processarTurnoMonstro();
        }
    } catch (const RPGException& e) {
        logarInfo(QString("Erro: ") + e.what());
        QMessageBox::warning(this, "Ação Inválida", e.what());
    }
}

void MainWindow::processarTurnoMonstro() {
    auto heroi = GerenciadorJogo::get_instancia().get_heroi();
    auto monstroAtual = GerenciadorJogo::get_instancia().get_monstro_atual();

    if (!emCombate || !monstroAtual || !heroi->is_vivo()) return;

    logarInfo("----------------- TURNO MONSTRO -----------------");
    int dano = monstroAtual->realizar_ataque();
    heroi->receber_dano(dano);

    atualizarFicha();

    if (!heroi->is_vivo()) {
        logarInfo("========================================");
        logarInfo("GAME OVER: Seu herói caiu na arena!");
        logarInfo("========================================");
        QMessageBox::critical(this, "Game Over", "Seu herói sucumbiu em batalha! O jogo terminou.");
        emCombate = false;
        atualizarArena();
        close();
    }
}

void MainWindow::verificarFimDeCombate() {
    auto heroi = GerenciadorJogo::get_instancia().get_heroi();
    auto monstroAtual = GerenciadorJogo::get_instancia().get_monstro_atual();

    if (!monstroAtual) return;

    if (!monstroAtual->is_vivo()) {
        logarInfo("========================================");
        logarInfo("VITÓRIA! Você derrotou o " + QString::fromStdString(monstroAtual->get_nome()));
        logarInfo("========================================");

        // Experiência via sobrecarga de operadores (heroi + exp)
        int expGanhar = 50 * monstroAtual->get_nivel();
        *heroi + expGanhar; // Adiciona XP usando operador +

        // Gerar Drop Aleatório (Factory no Combate)
        int chance = rand() % 100;
        std::shared_ptr<Item> drop = nullptr;
        if (chance < 40) {
            int tipo = rand() % 3;
            if (tipo == 0) drop = std::make_shared<Pocao>("Poção de Vida", "Restaura 50 de vida", 0.5, 5, 50);
            if (tipo == 1) drop = std::make_shared<PocaoEnergia>("Poção de Mana", "Restaura 30 de energia", 0.5, 5, 30);
            if (tipo == 2) drop = std::make_shared<BombaCaseira>("Bomba Menor", "Causa 20 de dano", 1.0, 10, 20);
        } else if (chance < 70) {
            int tipo = rand() % 4;
            if (tipo == 0) drop = std::make_shared<Arma>("Espada de Aço", "Arma cortante", 3.0, 10, 20);
            if (tipo == 1) drop = std::make_shared<Arma>("Cajado Místico", "Arma mágica", 2.0, 12, 15);
            if (tipo == 2) drop = std::make_shared<Arma>("Arco Longo", "Ataque à distância", 3.0, 15, 18);
            if (tipo == 3) drop = std::make_shared<Armadura>("Escudo de Madeira", "Proteção básica", 5.0, 10, 10);
        } else {
            int tipo = rand() % 5;
            if (tipo == 0) drop = std::make_shared<Armadura>("Capacete de Ferro", "Protege a cabeça", 3.0, 12, 10);
            if (tipo == 1) drop = std::make_shared<Armadura>("Peitoral de Aço", "Protege o torso", 8.0, 30, 20);
            if (tipo == 2) drop = std::make_shared<Armadura>("Bota de Couro", "Protege os pés", 2.0, 8, 5);
            if (tipo == 3) drop = std::make_shared<Armadura>("Anel da Força", "Aumenta atributos", 0.1, 15, 5);
            if (tipo == 4) drop = std::make_shared<Armadura>("Colar Mágico", "Aumenta resistência", 0.2, 20, 8);
        }

        if (drop) {
            try {
                *heroi + drop; // Adiciona item usando operador +
                logarInfo("O monstro dropou: " + QString::fromStdString(drop->get_nome()) + " que foi adicionado ao seu inventário.");
            } catch (const InventarioException& e) {
                logarInfo(QString("O monstro dropou um item, mas: ") + e.what());
            }
        }

        int progressoBatalha = GerenciadorJogo::get_instancia().get_progresso_batalha() + 1;
        GerenciadorJogo::get_instancia().set_progresso_batalha(progressoBatalha);
        emCombate = false;
        
        GerenciadorJogo::get_instancia().set_monstro_atual(nullptr);

        atualizarFicha();
        atualizarInventario();
        atualizarEquipados();
        atualizarArena();

        if (progressoBatalha >= 5) {
            QMessageBox::information(this, "Vitória Suprema!", "PARABÉNS! Você derrotou todos os monstros na Arena!\nO Reino está a salvo!");
        }
    }
}

void MainWindow::onSalvarJogo() {
    auto heroi = GerenciadorJogo::get_instancia().get_heroi();
    int prog = GerenciadorJogo::get_instancia().get_progresso_batalha();
    if (!heroi || emCombate) return;
    try {
        Persistencia::salvarJogo(heroi, "savegame.txt", prog);
        QMessageBox::information(this, "Salvar", "Jogo salvo com sucesso em savegame.txt!");
    } catch (const PersistenciaException& e) {
        QMessageBox::warning(this, "Erro", e.what());
    }
}
