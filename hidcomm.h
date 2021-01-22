#ifndef HIDCOMM_H
#define HIDCOMM_H
#include "hidapi.h"
#include "functional"
#include <QVector>
#include <QList>
#include <QThread>
#include <QDebug>
#include <map>
#include "writefunctioncheck.h"
#include "hidbasehandle.h"

class HidComm:public WriteFunctionCheck, public QThread,public HidBaseHandle
{
    struct writedata_coordinate
    {
        int x;
        int y;
    };
public:
    HidComm& operator=(const HidComm&)=delete;

    QString get_key_value(const int& deviceID, QString key);
    size_t get_write_coordinate(writedata_coordinate&);
    void parse_opus_data();
    bool get_hid_open_status(void){return hid_open_flag;}
    static HidComm &get_instance(){
        static HidComm instance;
        return instance;
    }
    hid_device *get_hid_handle(void){return hid_handle;}
    void ansStatusHandle(QByteArray& data);
    const std::map<int, std::map<QString, QString>>& get_deviceID_map(void){return deviceID_map;}
private:
    bool hid_open_flag=false;
    const char powerThreshold=5;
    QVector <writedata_coordinate> coordinate_vector;
    hid_device *hid_handle;

    std::map<int, std::map<QString, QString>> deviceID_map;
    HidComm(const HidComm&)=delete ;
    HidComm();
    void hid_read_loop(void);
    void get_binddeviceID(QByteArray& data);
    void set_testDeviceID(QByteArray& data);
    void run(){hid_read_loop();}

};

#endif // HIDCOMM_H
