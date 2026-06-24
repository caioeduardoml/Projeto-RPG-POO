#ifndef MAINWINDOW_HPP
#define MAINWINDOW_HPP

#include <QMainWindow>
#include <QProgressBar>
#include <QListWidget>
#include <QTextBrowser>
#include <QLabel>
#include <QPushButton>
#include <QComboBox>
#include <QLineEdit>
#include <QDialog>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QGridLayout>
#include <QGroupBox>

#include <iostream>
#include <streambuf>
#include <string>

#include "Personagem.hpp"
#include "Monstro.hpp"
#include "Item.hpp"
#include "Habilidade.hpp"
#include "Raca.hpp"
#include "Persistencia.hpp"

// Redirecionador de std::cout para o QTextBrowser
class QDebugStream : public std::basic_streambuf<char> {
public:
    QDebugStream(std::ostream &stream, QTextBrowser *text_edit) : m_stream(stream) {
        log_window = text_edit;
        m_old_buf = stream.rdbuf();
        stream.rdbuf(this);
    }
    ~QDebugStream() {
        m_stream.rdbuf(m_old_buf);
    }
protected:
    virtual int_type overflow(int_type v) {
        if (v == '\n') {
            log_window->append(QString::fromStdString(m_string));
            m_string.erase();
        } else if (v != EOF) {
            m_string += (char)v;
        }
        return v;
    }
private:
    std::ostream &m_stream;
    std::streambuf *m_old_buf;
    std::string m_string;
    QTextBrowser *log_window;
};

class MainWindow : public QMainWindow {
    Q_OBJECT
private:
    Personagem* heroi;
    int progressoBatalha;
    Monstro* monstroAtual;
    bool emCombate;

    QDebugStream* streamRedirector;

    // Painel Herói
    QLabel* lblNome;
    QLabel* lblClasseRaca;
    QLabel* lblNivelXP;
    QProgressBar* barVida;
    QProgressBar* barEnergia;

    // Painel Inventário
    QListWidget* listInventario;
    QListWidget* listEquipados;
    QPushButton* btnUsarItem;
    QPushButton* btnEquiparItem;
    QPushButton* btnDesequiparItem;

    // Painel Arena
    QGroupBox* grpArena;
    QLabel* lblMonstroStatus;
    QProgressBar* barVidaMonstro;
    QComboBox* comboHabilidades;
    QPushButton* btnAtaqueBasico;
    QPushButton* btnUsarHabilidade;
    QPushButton* btnIniciarArena;
    QTextBrowser* textLogs;

    // Ações globais
    QPushButton* btnSalvar;

    void atualizarFicha();
    void atualizarInventario();
    void atualizarEquipados();
    void atualizarArena();
    void logarInfo(const QString& msg);
    void processarTurnoMonstro();
    void verificarFimDeCombate();

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    bool mostrarWelcomeDialog();

private slots:
    void onUsarItem();
    void onEquiparItem();
    void onDesequiparItem();
    void onIniciarArena();
    void onAtaqueBasico();
    void onUsarHabilidade();
    void onSalvarJogo();
    void onItemSelected();
    void onEquipadoSelected();
};

#endif // MAINWINDOW_HPP
