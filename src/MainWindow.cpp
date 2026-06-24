#include "../include/MainWindow.hpp"
#include "../include/Guerreiro.hpp"
#include "../include/Mago.hpp"
#include "../include/Druida.hpp"
#include "../include/Arqueiro.hpp"
#include "../include/Ladrao.hpp"
#include "../include/ConstrutorEnergia.hpp"
#include "../include/Clerigo.hpp"

#include <QMessageBox>
#include <QFormLayout>
#include <QInputDialog>
#include <QDebug>
#include <QSplitter>
#include <fstream>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), heroi(nullptr), progressoBatalha(0), monstroAtual(nullptr), emCombate(false), streamRedirector(nullptr) {
    
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
    
    QLabel* lblNrgBar = new QLabel("Energia:", grpHeroi);
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
}

MainWindow::~MainWindow() {
    delete streamRedirector;
    if (heroi) {
        delete heroi;
    }
    if (monstroAtual) {
        delete monstroAtual;
    }
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
            heroi = Persistencia::carregarJogo("savegame.txt", progressoBatalha);
            if (heroi) {
                inicializado = true;
                welcomeDialog.accept();
            } else {
                QMessageBox::warning(&welcomeDialog, "Erro", "Erro ao ler savegame.txt!");
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

            Raca* raca = nullptr;
            int choiceRaca = cbRaca->currentIndex();
            switch (choiceRaca) {
                case 0: raca = new Humano(); break;
                case 1: raca = new Elfo(); break;
                case 2: raca = new Anao(); break;
                case 3: raca = new Orc(); break;
                case 4: raca = new Dragao(); break;
                default: raca = new Humano(); break;
            }

            int choiceClass = cbClasse->currentIndex();
            switch (choiceClass) {
                case 0: heroi = new Guerreiro(nome.toStdString(), raca, 1); break;
                case 1: heroi = new Mago(nome.toStdString(), raca, 1); break;
                case 2: heroi = new Arqueiro(nome.toStdString(), raca, 1); break;
                case 3: heroi = new Druida(nome.toStdString(), raca, 1); break;
                case 4: heroi = new Ladrao(nome.toStdString(), raca, 1); break;
                case 5: heroi = new ConstrutorEnergia(nome.toStdString(), raca, 1); break;
                case 6: heroi = new Clerigo(nome.toStdString(), raca, 1); break;
                default: heroi = new Guerreiro(nome.toStdString(), raca, 1); break;
            }

            // Sobrecarga de operador + para itens e experiência iniciais
            *heroi + new Arma("Espada de Aço", "Arma cortante afiada", 3.0f, 15.0f);
            *heroi + new Pocao("Poção de Cura", "Restaura 50 de vida", 0.5f, 50.0f);
            *heroi + new PocaoEnergia("Poção de Energia", "Restaura 30 de energia", 0.5f, 30.0f);
            *heroi + new ItemEspecial("Cristal Divino", "Restaura 25 de energia", 0.2f, 25.0f);
            *heroi + 10.0f; // Adiciona 10 XP usando operador +

            inicializado = true;
            progressoBatalha = 0;
            createDialog.accept();
            welcomeDialog.accept();
        });

        createDialog.exec();
    });

    welcomeDialog.exec();
    
    if (inicializado) {
        atualizarFicha();
        atualizarInventario();
        atualizarEquipados();
        atualizarArena();
        logarInfo("Seja bem-vindo, " + QString::fromStdString(heroi->getNome()) + "! Sua aventura se inicia agora.");
        return true;
    }
    return false;
}

void MainWindow::atualizarFicha() {
    if (!heroi) return;
    
    lblNome->setText(QString("Nome: %1").arg(QString::fromStdString(heroi->getNome())));
    lblClasseRaca->setText(QString("Classe: %1 | Raça: %2")
        .arg(QString::fromStdString(heroi->getClasseRPG()))
        .arg(QString::fromStdString(heroi->getRaca() ? heroi->getRaca()->getNomeRaca() : "Nenhuma")));
    
    // XP e Meta
    float xp = heroi->getExperiencia();
    // Meta XP é calculada internamente no core (100 * nivel)
    float metaXP = 100.0f * heroi->getNivel();
    lblNivelXP->setText(QString("Nível: %1 | XP: %2 / %3").arg(heroi->getNivel()).arg(xp).arg(metaXP));

    // Barras
    barVida->setMaximum(static_cast<int>(heroi->getMaxVida()));
    barVida->setValue(static_cast<int>(heroi->getVida()));
    barVida->setFormat(QString("%1/%2 HP").arg(static_cast<int>(heroi->getVida())).arg(static_cast<int>(heroi->getMaxVida())));

    // O core herda Energia (energia e maxEnergia) de Entidade
    // Na nossa versão, a energia base também é mantida
    // Vamos usar getVida e recuperarVida como espelhos se necessário, mas na verdade
    // o core tem atributos energia e maxEnergia herdados que estão protegidos.
    barEnergia->setMaximum(static_cast<int>(heroi->getMaxEnergia()));
    barEnergia->setValue(static_cast<int>(heroi->getEnergia()));
    barEnergia->setFormat(QString("%1/%2 EP").arg(static_cast<int>(heroi->getEnergia())).arg(static_cast<int>(heroi->getMaxEnergia())));
}

static QString obterEspecificacaoItem(Item* it) {
    if (!it) return "";
    
    if (it->getTipo() == TipoItem::Arma) {
        if (Arma* arma = dynamic_cast<Arma*>(it)) {
            return QString("(+%1 dano)").arg(static_cast<int>(arma->getDanoBonus()));
        }
    } else if (it->getTipo() == TipoItem::Armadura) {
        if (Armadura* armadura = dynamic_cast<Armadura*>(it)) {
            return QString("(+%1 defesa)").arg(static_cast<int>(armadura->getDefesaBonus()));
        }
    } else if (it->getTipo() == TipoItem::Pocao) {
        if (Pocao* pocao = dynamic_cast<Pocao*>(it)) {
            return QString("(+%1 cura)").arg(static_cast<int>(pocao->getCura()));
        }
    } else if (it->getTipo() == TipoItem::PocaoEnergia) {
        if (PocaoEnergia* pe = dynamic_cast<PocaoEnergia*>(it)) {
            return QString("(+%1 energia)").arg(static_cast<int>(pe->getEnergiaRestaurada()));
        }
    } else if (it->getTipo() == TipoItem::Bomba) {
        if (BombaCaseira* bomba = dynamic_cast<BombaCaseira*>(it)) {
            return QString("(+%1 dano)").arg(static_cast<int>(bomba->getDano()));
        }
    } else if (it->getTipo() == TipoItem::Especial) {
        if (ItemEspecial* ie = dynamic_cast<ItemEspecial*>(it)) {
            return QString("(+%1 energia)").arg(static_cast<int>(ie->getBonusStatus()));
        }
    }
    return "";
}

void MainWindow::atualizarInventario() {
    listInventario->clear();
    if (!heroi) return;

    Inventario& inv = heroi->getInventario();
    for (int i = 0; i < inv.getQuantidadeItens(); ++i) {
        Item* it = inv.getItem(i);
        if (it) {
            QString tipoStr = "";
            switch (it->getTipo()) {
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
                .arg(QString::fromStdString(it->getNome()))
                .arg(spec)
                .arg(it->getPeso())
                .arg(QString::fromStdString(it->getDescricao())));
        }
    }

    // Limpar seleção
    btnUsarItem->setEnabled(false);
    btnEquiparItem->setEnabled(false);
}

void MainWindow::atualizarEquipados() {
    listEquipados->clear();
    if (!heroi) return;

    // Arma equipada
    if (Arma* arma = heroi->getArmaEquipada()) {
        QString spec = obterEspecificacaoItem(arma);
        listEquipados->addItem(QString("[Arma] %1 %2")
            .arg(QString::fromStdString(arma->getNome()))
            .arg(spec));
    } else {
        listEquipados->addItem("[Arma] Nenhuma");
    }

    // Armaduras equipadas
    const auto& armaduras = heroi->getArmadurasEquipadas();
    for (auto const& [slot, armadura] : armaduras) {
        if (armadura) {
            QString spec = obterEspecificacaoItem(armadura);
            listEquipados->addItem(QString("[%1] %2 %3")
                .arg(QString::fromStdString(slot))
                .arg(QString::fromStdString(armadura->getNome()))
                .arg(spec));
        }
    }
    
    btnDesequiparItem->setEnabled(false);
}

void MainWindow::atualizarArena() {
    if (emCombate && monstroAtual) {
        lblMonstroStatus->setText(QString("Inimigo: %1 (Nv.%2)")
            .arg(QString::fromStdString(monstroAtual->getNome()))
            .arg(monstroAtual->getNivel()));
        barVidaMonstro->setEnabled(true);
        barVidaMonstro->setMaximum(static_cast<int>(monstroAtual->getMaxVida()));
        barVidaMonstro->setValue(static_cast<int>(monstroAtual->getVida()));
        barVidaMonstro->setFormat(QString("%1/%2 HP").arg(static_cast<int>(monstroAtual->getVida())).arg(static_cast<int>(monstroAtual->getMaxVida())));
        
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
        // Preenche combobox com habilidades aprendidas
        // Precisamos consultar as habilidades
        // Como o heroi tem `listarHabilidades() const` que imprime, mas não expõe o vetor publicamente diretamente de forma limpa,
        // vamos recuperar através de indexações até `escolherHabilidade`.
        int idx = 0;
        while (true) {
            Habilidade* hab = heroi->escolherHabilidade(idx);
            if (!hab) break;
            comboHabilidades->addItem(QString("%1 %2").arg(QString::fromStdString(hab->getNome())).arg(QString::fromStdString(hab->getEfeitoStr())));
            idx++;
        }
    }
}

void MainWindow::logarInfo(const QString& msg) {
    textLogs->append("<font color='#00ffcc'><b>[SISTEMA]</b></font> " + msg);
}

void MainWindow::onItemSelected() {
    int idx = listInventario->currentRow();
    if (idx < 0) {
        btnUsarItem->setEnabled(false);
        btnEquiparItem->setEnabled(false);
        return;
    }

    Item* item = heroi->getInventario().getItem(idx);
    if (!item) {
        btnUsarItem->setEnabled(false);
        btnEquiparItem->setEnabled(false);
        return;
    }

    if (item->getTipo() == TipoItem::Arma || item->getTipo() == TipoItem::Armadura) {
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
    int idx = listInventario->currentRow();
    if (idx < 0) return;

    Item* item = heroi->getInventario().getItem(idx);
    if (!item) return;

    // Usar item
    logarInfo("----------------------------------------");
    item->usar(heroi, monstroAtual);

    // Consumir
    heroi->getInventario().removerItem(item);
    delete item;

    atualizarFicha();
    atualizarInventario();
    atualizarEquipados();
    atualizarArena();
    
    if (emCombate) {
        processarTurnoMonstro();
    }
}

void MainWindow::onEquiparItem() {
    int idx = listInventario->currentRow();
    if (idx < 0) return;

    Item* item = heroi->getInventario().getItem(idx);
    if (!item) return;

    logarInfo("----------------------------------------");
    item->usar(heroi, nullptr); // Equipa o item no herói

    atualizarFicha();
    atualizarInventario();
    atualizarEquipados();
    atualizarArena();
}

void MainWindow::onDesequiparItem() {
    int idx = listEquipados->currentRow();
    if (idx < 0) return;

    QListWidgetItem* selected = listEquipados->item(idx);
    if (!selected) return;

    QString text = selected->text();
    if (text.isEmpty() || text.endsWith("Nenhuma")) return;

    logarInfo("----------------------------------------");
    if (text.startsWith("[Arma]")) {
        heroi->desequiparArma();
    } else {
        // Encontra o slot extraindo o texto entre colchetes
        int endBracket = text.indexOf(']');
        if (endBracket > 1) {
            QString slot = text.mid(1, endBracket - 1);
            heroi->desequiparArmadura(slot.toStdString());
        }
    }

    atualizarFicha();
    atualizarInventario();
    atualizarEquipados();
    atualizarArena();
}

void MainWindow::onIniciarArena() {
    if (progressoBatalha >= 5) return;

    logarInfo("========================================");
    logarInfo(QString("INICIANDO DESAFIO %1/5 DA ARENA!").arg(progressoBatalha + 1));
    logarInfo("========================================");

    switch(progressoBatalha) {
        case 0: monstroAtual = new Goblin(); break;
        case 1: monstroAtual = new OrcMonstro(); break;
        case 2: monstroAtual = new LoboMau(); break;
        case 3: monstroAtual = new GiganteMalvado(); break;
        case 4: monstroAtual = new PeppaPig(); break;
    }

    // Restaurar a vida e energia do herói ao iniciar um combate na arena
    heroi->recuperarVida(heroi->getMaxVida());
    heroi->recuperarEnergia(heroi->getMaxEnergia());
    atualizarFicha();

    emCombate = true;
    atualizarArena();
}

void MainWindow::onAtaqueBasico() {
    if (!emCombate || !monstroAtual) return;

    logarInfo("----------------- TURNO JOGADOR -----------------");
    std::cout << heroi->getNome() << " realiza um ataque básico!\n";
    monstroAtual->receberDano(heroi->getDanoTotal());
    
    // Recupera 15 de energia por realizar ataque básico
    heroi->recuperarEnergia(15.0f);
    std::cout << heroi->getNome() << " recuperou 15 de energia pelo ataque básico.\n";

    atualizarFicha();
    atualizarArena();
    verificarFimDeCombate();

    if (emCombate) {
        processarTurnoMonstro();
    }
}

void MainWindow::onUsarHabilidade() {
    if (!emCombate || !monstroAtual) return;

    int idx = comboHabilidades->currentIndex();
    Habilidade* hab = heroi->escolherHabilidade(idx);
    if (!hab) return;

    logarInfo("----------------- TURNO JOGADOR -----------------");
    
    // Gasta energia da entidade
    if (heroi->gastarEnergia(hab->getCustoEnergia())) {
        hab->usar(heroi, monstroAtual);
        atualizarFicha();
        atualizarArena();
        verificarFimDeCombate();

        if (emCombate) {
            processarTurnoMonstro();
        }
    } else {
        logarInfo("Erro: Energia insuficiente para conjurar esta habilidade!");
    }
}

void MainWindow::processarTurnoMonstro() {
    if (!emCombate || !monstroAtual || !heroi->isVivo()) return;

    logarInfo("----------------- TURNO MONSTRO -----------------");
    float dano = monstroAtual->realizarAtaque();
    heroi->receberDano(dano);

    atualizarFicha();

    if (!heroi->isVivo()) {
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
    if (!monstroAtual) return;

    if (!monstroAtual->isVivo()) {
        logarInfo("========================================");
        logarInfo("VITÓRIA! Você derrotou o " + QString::fromStdString(monstroAtual->getNome()));
        logarInfo("========================================");

        // Experiência e drops via sobrecarga de operadores (heroi + exp e heroi + item)
        float expGanhar = 50.0f * monstroAtual->getNivel();
        *heroi + expGanhar; // Adiciona XP usando operador +

        // Gerar Drop Aleatório (Strategy/Factory no Combate)
        int chance = rand() % 100;
        Item* drop = nullptr;
        if (chance < 40) {
            int tipo = rand() % 3;
            if (tipo == 0) drop = new Pocao("Poção de Vida", "Restaura 50 de vida", 0.5f, 50.0f);
            if (tipo == 1) drop = new PocaoEnergia("Poção de Mana", "Restaura 30 de energia", 0.5f, 30.0f);
            if (tipo == 2) drop = new BombaCaseira("Bomba Menor", "Causa 20 de dano", 1.0f, 20.0f);
        } else if (chance < 70) {
            int tipo = rand() % 4;
            if (tipo == 0) drop = new Arma("Espada de Aço", "Arma cortante", 3.0f, 20.0f);
            if (tipo == 1) drop = new Arma("Cajado Místico", "Arma mágica", 2.0f, 15.0f);
            if (tipo == 2) drop = new Arma("Arco Longo", "Ataque à distância", 3.0f, 18.0f);
            if (tipo == 3) drop = new Armadura("Escudo de Madeira", "Proteção básica", 5.0f, 10.0f);
        } else {
            int tipo = rand() % 5;
            if (tipo == 0) drop = new Armadura("Capacete de Ferro", "Protege a cabeça", 3.0f, 10.0f);
            if (tipo == 1) drop = new Armadura("Peitoral de Aço", "Protege o torso", 8.0f, 20.0f);
            if (tipo == 2) drop = new Armadura("Bota de Couro", "Protege os pés", 2.0f, 5.0f);
            if (tipo == 3) drop = new Armadura("Anel da Força", "Aumenta atributos", 0.1f, 5.0f);
            if (tipo == 4) drop = new Armadura("Colar Mágico", "Aumenta resistência", 0.2f, 8.0f);
        }

        if (drop) {
            *heroi + drop; // Adiciona item usando operador +
            logarInfo("O monstro dropou: " + QString::fromStdString(drop->getNome()) + " que foi adicionado ao seu inventário.");
        }

        progressoBatalha++;
        emCombate = false;
        
        delete monstroAtual;
        monstroAtual = nullptr;

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
    if (!heroi || emCombate) return;
    if (Persistencia::salvarJogo(heroi, "savegame.txt", progressoBatalha)) {
        QMessageBox::information(this, "Salvar", "Jogo salvo com sucesso em savegame.txt!");
    } else {
        QMessageBox::warning(this, "Erro", "Não foi possível salvar o jogo.");
    }
}
