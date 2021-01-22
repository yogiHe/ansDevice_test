#include "hidcomm.h"
#include "crc16/crc16.h"
#include "string.h"
#include "QTextCodec"

HidComm::HidComm()
{
    start();
}

QString HidComm::get_key_value(const int& deviceID, QString key)
{
    for(auto &it : deviceID_map){
        if(it.first == deviceID){
            for(auto &info : deviceID_map[deviceID]){
                if(info.first == key){
                    QString keyValue = deviceID_map[deviceID][key];
                    deviceID_map[deviceID][key].clear();
                    return keyValue;
                }
            }
        }
    }
    return nullptr;
}
/*0x4e*/
void HidComm::ansStatusHandle(QByteArray& data)
{
    int device_id;
    char device_power;
    char charge_flag;
    std::map<int, std::map<QString, QString>>::iterator it;
    for(int i=0; i<18; i++){
        if((device_id = *reinterpret_cast<int *>(data.data()+(8+9*i))) == 0)break;
        device_power = data.at(8+9*i+4+1);
        charge_flag = data.at(8+9*i+4);
        it = deviceID_map.find(device_id);
        if(charge_flag == 1){
            if(it!=deviceID_map.end()){
                deviceID_map[device_id]["power"] = device_power;
            }
            else {
                std::map<QString, QString> device_info;
                device_info["power"] = device_power;
                deviceID_map.insert(std::pair<int, std::map<QString, QString>>(device_id, device_info));
            }
            if(device_power > powerThreshold){
                QTextCodec *gb2312 = QTextCodec::codecForName("gb2312");
                send_show_message(device_id, gb2312->fromUnicode("按下语音键开始测试"), hid_handle);
            }
            else {
                QTextCodec *gb2312 = QTextCodec::codecForName("gb2312");
                send_show_message(device_id, gb2312->fromUnicode("电量不足请继续充电"), hid_handle);
            }

        }
        else {
            for(auto sencond: deviceID_map[device_id]){
                if(sencond.first == testDone){
                    deviceID_map.erase(it);
                }
            }
        }
    }

}

void HidComm::set_testDeviceID(QByteArray &data)
{
    int device_id = *reinterpret_cast<int *>(data.data()+8);
    for (auto it : deviceID_map) {
        if(it.first == device_id){
            if(deviceID_map[device_id]["power"] > powerThreshold){
                /*if(testingDeviceID != 0){
                    QTextCodec *gb2312 = QTextCodec::codecForName("gb2312");
                    send_show_message(testingDeviceID, gb2312->fromUnicode("测试被终止"), hid_handle);
                }*/
                deviceID_map[device_id][HidBaseHandle::testReady]=HidBaseHandle::testReady;
            }
            break;
        }
        qDebug()<<"it is"<<it.first;
    }
    qDebug()<<"deviceID_map size"<<deviceID_map.size();
}
void HidComm::hid_read_loop(void)
{
    //hid_device* handle;// = hid_open(0x0483, 0x5750, nullptr);
    unsigned char *hid_data_ptr = new unsigned char[512];
    int length = -1;
begin:
    hid_handle = openHid_untillopened();
    qDebug()<<"hid thread run"<<hid_handle;
    hid_open_flag = true;
    deviceID_map.clear();
    while (!QThread::currentThread()->isInterruptionRequested()){
        length = hid_read(hid_handle, hid_data_ptr, 512);
        QByteArray data(reinterpret_cast<char *>(hid_data_ptr), length);
        if(length > 0){
            switch (data.at(7)) {
                case 0x4e: ansStatusHandle(data); break;
                case 0x47: set_testDeviceID(data); break;
            }
        }
        else {
            goto begin;
        }
    }
}
