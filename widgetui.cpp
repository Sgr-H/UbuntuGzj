#include "widgetui.h"
#include "ui_widgetui.h"
//#include "ui_MainWindowsUI.h"
#include<qelapsedtimer.h>

WidgetUI::WidgetUI(QWidget *parent)
    : FramelessWidget(parent)
    , ui(new Ui::WidgetUI)
{
    ui->setupUi(this);
    init();
    initWidgetUI();
    UIConnect();

}

WidgetUI::~WidgetUI()
{
    delete ui;
}

void WidgetUI::init()
{
    flashElec=new QTimer;
    flashElec->start(1000);
    bridgeManagerThread=new QThread;
    BridgeManager::instance().moveToThread(bridgeManagerThread);
    bridgeManagerThread->start();

}

void WidgetUI::initWidgetUI()
{
    //设置标题栏控件
    //    this->showMaximized();
    this->setTitleBar(ui->labTitle);
    //关联信号

    //设置样式表
    QStringList list;
    list << "#titleBar{background-color:#09233e;}";
    //    list << "#titleBar{border-top-left-radius:4px;border-top-right-radius:4px;}";
    list << "#widgetMain{border:1px solid #041d48;background-image: url(:/images/bg.png);}";
    //list << "#widgetMain{border-bottom-left-radius:8px;border-bottom-right-radius:8px;}";
    this->setStyleSheet(list.join(""));
    int font_id = QFontDatabase::addApplicationFont(":/Fonts/iconfont.ttf");
    QString font_name = QFontDatabase::applicationFontFamilies(font_id).at(0);
    iconfont = QFont(font_name);
    iconfont.setPixelSize(16);

    //    //最小化
    //    ui->btnMenu_Min->setFont(iconfont);
    //    ui->btnMenu_Min->setText(QChar(0xe729));
    //    //最大化
    //    ui->btnMenu_Max->setFont(iconfont);
    //    ui->btnMenu_Max->setText(QChar(0xe720));
    //    //关闭
    //    ui->btnMenu_Close->setFont(iconfont);
    //    ui->btnMenu_Close->setText(QChar(0xe610));


    //    QSqlDatabase sqlDatabase = QSqlDatabase::database("qt_sql_default_connection");
    //    //规定格式
    //    model = new QSqlTableModel(this, sqlDatabase);
    //    model->setTable("elecM");
    //    model->setEditStrategy(QSqlTableModel::OnFieldChange);
    //    model->select();
    //    model->setHeaderData(model->fieldIndex("id"),
    //                         Qt::Horizontal, tr("编号"));
    //    model->setHeaderData(model->fieldIndex("addr"),
    //                         Qt::Horizontal, tr("地址"));
    //    model->setHeaderData(model->fieldIndex("elecQ"),
    //                         Qt::Horizontal, tr("电量"));
    //            if(tableNameList.count()!=0)
    ui->mainElecTableView->setModel(BridgeManager::instance().electrityMIns()->getModel());
    ui->mainWaterTableView->setModel(BridgeManager::instance().waterMIns()->getModel());

}

void WidgetUI::UIConnect()
{

    //主界面 ---> 通用设置界面
    connect(ui->CommonSettingPushButton,&QPushButton::clicked,this,[=]{
        this->hide();
        BridgeManager::instance().commonSINS()->show();
    });
    //page2按钮通用跳转
    connect(ui->btnMenu_Max,&QPushButton::clicked,ui->CommonSettingPushButton,&QPushButton::clicked);
    //主界面 ---> 电表界面
    connect(ui->mainElecPushButton,&QPushButton::clicked,this,[=]{
        this->hide();
        BridgeManager::instance().electrityMIns()->show();
    });
    //page2按钮电表跳转
    connect(ui->pushButton_6,&QPushButton::clicked,ui->mainElecPushButton,&QPushButton::clicked);
    //主界面 ---> 水表界面
    connect(ui->mainWaterPushButton,&QPushButton::clicked,this,[=]{
        this->hide();
        BridgeManager::instance().waterMIns()->show();
    });
    //page2按钮水表跳转
    connect(ui->pushButton_13,&QPushButton::clicked,ui->mainWaterPushButton,&QPushButton::clicked);

    //主界面 ---> 环境界面
    connect(ui->envirPushButton,&QPushButton::clicked,this,[=]{
        this->hide();
        BridgeManager::instance().environmentMIns()->show();
    });
    //page2按钮环境跳转
    connect(ui->pushButton_5,&QPushButton::clicked,ui->envirPushButton,&QPushButton::clicked);

    //主界面 ---> 消防界面
    connect(ui->mainFirePushButton,&QPushButton::clicked,this,[=]{
        this->hide();
        BridgeManager::instance().firePINS()->show();
    });
    //page2按钮消防跳转
    connect(ui->pushButton_2,&QPushButton::clicked,ui->mainFirePushButton,&QPushButton::clicked);

    //主界面 ---> 水位界面
    connect(ui->mainWaterLeverPushButton,&QPushButton::clicked,this,[=]{
        this->hide();
        BridgeManager::instance().waterLIns()->show();
    });
    //page2按钮水位跳转
    connect(ui->pushButton_3,&QPushButton::clicked,ui->mainWaterLeverPushButton,&QPushButton::clicked);

    //主界面 ---> 电梯界面
    connect(ui->mainLiftPushButton,&QPushButton::clicked,this,[=]{
        this->hide();
        BridgeManager::instance().liftMIns()->show();
    });
    //page2按钮电梯跳转
    connect(ui->pushButton_4,&QPushButton::clicked,ui->mainLiftPushButton,&QPushButton::clicked);

    //通用设置界面 ---> 主界面
    connect(BridgeManager::instance().commonSINS(),&CommonSetting::showWidgetUI,this,&WidgetUI::show);
    //电表界面    --->主界面
    connect(BridgeManager::instance().electrityMIns(),&ElectricityMeter::showWidgetUI,this,&WidgetUI::show);
    //水表界面    --->主界面
    connect(BridgeManager::instance().waterMIns(),&WaterMeter::showWidgetUI,this,&WidgetUI::show);
    //环境界面    --->主界面
    connect(BridgeManager::instance().environmentMIns(),&Environment::showWidgetUI,this,&WidgetUI::show);
    //消防界面    --->主界面
    connect(BridgeManager::instance().firePINS(),&FireP::showWidgetUI,this,&WidgetUI::show);
    //水位界面    --->主界面
    connect(BridgeManager::instance().waterLIns(),&WaterLever::showWidgetUI,this,&WidgetUI::show);
    //电梯界面    --->主界面
    connect(BridgeManager::instance().liftMIns(),&LiftManager::showWidgetUI,this,&WidgetUI::show);

    //其他按钮 控制 轮询开始
        connect(ui->pushButton_14,&QPushButton::clicked,BridgeManager::instance().serialIns(),&SerialSetting::elecPollingStart);
    //其他按钮 控制 清表
//    connect(ui->pushButton_14,&QPushButton::clicked,BridgeManager::instance().gzjSqliteINS(),&GzjSqlite::clear);
    //变配电按钮
    connect(ui->pushButton_15,&QPushButton::clicked,[=]{



        QElapsedTimer mstimer;
            mstimer.start();
            qDebug()<<"ses"<<endl;

//        for (int var = 0; var < 5; ++var) {
//        BridgeManager::instance().serialIns()->serialPort2->write(QByteArray::fromHex("6666"));
//        BridgeManager::instance().serialIns()->serialPort1->write("666");
//        }
        float time1 = (double)mstimer.nsecsElapsed()/(double)1000000;
            qDebug() << time1<<"ms";// 最终统计出来是ms
//        float time2 = (double)mstimer.nsecsElapsed()/(double)1000000;
//            qDebug() << time2<<"ms";// 最终统计出来是ms


//        QVector <QPair<int,QString>> sss1;
//        QPair <int,QString> fc1;
//        QSqlQuery sql_query(BridgeManager::instance().gzjSqliteINS()->sqlDatabase);
//        QString temp_select="select deviceInfo.target_type,collect_instruct,device_Addr,serial_Port,upload_frequency from deviceInfo join "
//                            "configuration on deviceInfo.target_type=configuration.target_type";
//        if(!sql_query.exec(temp_select))
//            qDebug()<<"fail ,erro1";
//        while(sql_query.next()){
//            QString temp_zhiling;
//            temp_zhiling.append(sql_query.value(2).toByteArray());
//            temp_zhiling.append(sql_query.value(1).toString());
//            quint16 temp_frequence=sql_query.value(4).toUInt();
//            QString temp_zhiling_increase0 = QString("%1").arg(temp_zhiling, 12, QLatin1Char('0'));
//            fc1.first=temp_frequence;fc1.second=temp_zhiling_increase0;
//            bool flagcc=false;
//            for( QPair<int,QString> temp999 : sss1)
//                if(!temp999.second.compare(temp_zhiling_increase0)){
//                    flagcc=true;
//                    qDebug()<<"111";
//                }
//            if(!flagcc)
//            sss1.append(fc1);

//            //qDebug()<<QByteArray::fromHex(temp_zhiling.toLatin1());
//        }

//        for (auto temp555 : sss1) {

//            qDebug()<<temp555.first<<temp555.second;
//        }



//        qDebug()<<sss1.at(1).first<<sss1.at(1).second;
//        if(sss1.at(1)){
//            qDebug()<<"ssss"<<endl;
//        }

        //清表
        //        BridgeManager::instance().gzjSqliteINS()->clear();
        //批量插入数据
        //        quint16 tmp1;QString tmp2; QString tmp3;QString tmp4;
        //        for (int var = 0; var < 6000; ++var) {
        //            tmp1=var;
        //            tmp2="电量";
        //            tmp3="ss";
        //            tmp4=QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss");
        //            BridgeManager::instance().gzjSqliteINS()->insert(tmp1,tmp2,tmp3,tmp4,"elecMh");
        //        }
    });

    //接受数据变动
    connect(BridgeManager::instance().serialSMINS(),&SerialSettingManager::process_msg,[this](const quint8 &_info_port,const QString &_string_data){
        if(_info_port==1)
            ui->label_15->setText(_string_data);
    });

    connect(this,&WidgetUI::signtest,&BridgeManager::instance(),&BridgeManager::signtest);

    //定时器刷新界面
    connect(flashElec,&QTimer::timeout,this,[=]{
        if(elecRowPos>=BridgeManager::instance().electrityMIns()->getElecMaxAddr()-1)
            elecRowPos=0;
        QModelIndex index=ui->mainElecTableView->model()->index(elecRowPos++,0);
        ui->mainElecTableView->scrollTo(index,QAbstractItemView::PositionAtTop);
    });
}



void WidgetUI::on_pushButton_clicked()
{
    emit signtest();
}

void WidgetUI::on_aboutgzjPushButton_clicked()
{
    QMessageBox::about(this,"无锡冠之杰数据信息技术有限公司",QString("无锡冠之杰数据信息技术有限公司成立于2019年08月16日，注册地位于无锡市梁溪区南湖大道588号14楼，法定代表人为岳阳。经营范围包括通讯信息技术、物联网技术、计算机、软件及辅助设备、网络技术、工业自动化控制设备、楼宇智能化控制设备的技术开发、技术服务、技术咨询；数据处理与存储服务；信息系统集成服务；监控设备的安装、维修；企业管理咨询；电子产品、仪器仪表、专用设备的技术开发、销售。\n\n联系电话：0510-85400192"));
}



void WidgetUI::on_btnMenu_Min_clicked()
{
    if(switchPage>2)
        switchPage=0;
    ui->stackedWidget->setCurrentIndex(switchPage++);
}
