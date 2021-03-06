//
// Created by chang on 2017-07-28.
//

#ifndef SERIALWIZARD_MAINWINDOW_H
#define SERIALWIZARD_MAINWINDOW_H

class QPushButton;

class QComboBox;

class QTextBrowser;

class QCheckBox;

class QLineEdit;

class QLabel;

class QTextEdit;

class QTimer;

class SerialSettings;

class AbstractReadWriter;

class QRadioButton;

class QButtonGroup;

class SerialController;

#include <QtWidgets/QMainWindow>
#include "FrameInfoDialog.h"

struct RunConfig {
    QString lastDir;
    QString lastFilePath;
};

class MainWindow : public QMainWindow {
Q_OBJECT
public:
    explicit MainWindow(QWidget *parent = nullptr);

    enum class SerialType {
        Normal = 1,
        TcpServer,
        TcpClient,
        Bridge,
        SerialBridge,
    };

    enum class LineReturn {
        RN = 1,
        R,
        N,
    };

    void init();

    void initUi();

    void createConnect();

    void createStatusBar();

    ~MainWindow() override;

    enum class SendType {
        Line
    };

public:

signals:

    void serialStateChanged(bool);

    void writeBytesChanged(qint64 bytes);

    void readBytesChanged(qint64 bytes);

    void currentWriteCountChanged(qint64 count);

public slots:

    void openReadWriter();

    void closeReadWriter();

    void sendNextData();

    void readData();

    qint64 writeData(const QByteArray &data);

    void setOpenButtonText(bool isOpen);

    void displayReceiveData(const QByteArray &data);

    void displaySentData(const QByteArray &data);

    void open();

    void save();

    void tool();

    void openDataValidator();

    void openConvertDataDialog();

    void clearReceivedData();

    void saveReceivedData();

    void clearSentData();

    void saveSentData();

    void handlerSerialNotOpen();

    void updateStatusMessage(const QString &message);

    void updateReadBytes(qint64 bytes);

    void updateWriteBytes(qint64 bytes);

    void updateCurrentWriteCount(qint64 count);

    void updateTcpClient(const QString &address, qint16 port);

    void clearTcpClient();

    void updateSendType();

private:

    enum class AutoSendState {
        NotStart, Sending, Finish
    };

    bool isReadWriterOpen();

    bool isReadWriterConnected();

    void readSettings();

    void writeSettings();

    void createActions();

    void createMenu();

    void updateSendData(bool isHex, const QString &text);

    void updateSerialPortNames();

    void updateReceiveCount(qint64 count);

    void startAutoSendTimerIfNeed();

    void stopAutoSend();

    void resetSendButtonText();

    void updateTotalSendCount(qint64 count);

    void showReadData(const QByteArray &data);

    void showSendData(const QByteArray &data);

    QStringList getSerialNameList();

    RunConfig *runConfig{nullptr};

    //?????????
    QLabel *statusBarReadBytesLabel;
    QLabel *statusBarWriteBytesLabel;
    QPushButton *statusBarResetCountButton;

    QMenu *fileMenu;
    QMenu *editMenu;
    QMenu *toolMenu;
    QMenu *helpMenu;

    QAction *openAct;
    QAction *saveAct;
    QAction *exitAct;
    QAction *validateDataAct;
    QAction *convertDataAct;

    AbstractReadWriter *_readWriter{nullptr};

    qint64 sendCount{0};
    qint64 receiveCount{0};

    QRadioButton *serialRadioButton;
    QRadioButton *tcpServerRadioButton;
    QRadioButton *tcpClientRadioButton;
    QRadioButton *bridgeRadioButton;
    QRadioButton *serialBridgeRadioButton;

    QButtonGroup *readWriterButtonGroup;

    // ????????????
    QComboBox *serialPortNameComboBox;
    QComboBox *serialPortBaudRateComboBox;
    QComboBox *serialPortParityComboBox;
    QComboBox *serialPortDataBitsComboBox;
    QComboBox *serialPortStopBitsComboBox;
    QPushButton *openSerialButton;
    QPushButton *refreshSerialButton;

    // ??????????????????
    QComboBox *secondSerialPortNameComboBox;
    QComboBox *secondSerialPortBaudRateComboBox;
    QComboBox *secondSerialPortParityComboBox;
    QComboBox *secondSerialPortDataBitsComboBox;
    QComboBox *secondSerialPortStopBitsComboBox;

    // TCP??????
    QLineEdit *tcpAddressLineEdit;
    QLineEdit *tcpPortLineEdit;
    QLabel *tcpClientLabel;

    // ????????????
    QCheckBox *addLineReturnCheckBox;
    QCheckBox *displayReceiveDataAsHexCheckBox;
    QCheckBox *pauseReceiveCheckBox;
    QPushButton *saveReceiveDataButton;
    QPushButton *clearReceiveDataButton;
    QCheckBox *addReceiveTimestampCheckBox;

    // ????????????
    QCheckBox *hexCheckBox;
    QCheckBox *displaySendDataCheckBox;
    QCheckBox *displaySendDataAsHexCheckBox;
    QCheckBox *autoSendCheckBox;
    QLineEdit *sendIntervalLineEdit;
    QLineEdit *emptyLineDelayLindEdit;
    QPushButton *saveSentDataButton;
    QPushButton *clearSentDataButton;

    QCheckBox *loopSendCheckBox;
    QPushButton *resetLoopSendButton;
    QLineEdit *currentSendCountLineEdit;
    QLabel *totalSendCountLabel;

    QTextBrowser *receiveDataBrowser;
    QTextBrowser *sendDataBrowser;

    QTextEdit *sendTextEdit;

    QPushButton *sendLineButton;
    QCheckBox *sendLineReturnCheckBox;
    QRadioButton *sendRNLineReturnButton;
    QRadioButton *sendRReturnLineButton;
    QRadioButton *sendNReturnLineButton;

    QButtonGroup *lineReturnButtonGroup;

    AutoSendState autoSendState{AutoSendState::NotStart};

    QTimer *autoSendTimer{nullptr};

    SerialController *serialController{nullptr};

    int totalSendCount{0};

    bool _loopSend{false};

    SendType _sendType{SendType::Line};

    SerialType _serialType{SerialType::Normal};

    int skipSendCount{0};

    QByteArray lineReturn;

    bool _dirty{true};
};

#endif //SERIALWIZARD_MAINWINDOW_H
