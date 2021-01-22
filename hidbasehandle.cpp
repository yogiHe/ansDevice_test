#include "hidbasehandle.h"
#include "crc16/crc16.h"


const QString HidBaseHandle::keyA = "keyA";
const QString HidBaseHandle::keyB = "keyB";
const QString HidBaseHandle::keyC = "keyC";
const QString HidBaseHandle::keyD = "keyD";
const QString HidBaseHandle::keyF = "keyF";
const QString HidBaseHandle::keyT = "keyT";
const QString HidBaseHandle::keyG = "keyG";
const QString HidBaseHandle::keyPress = "Press";
const QString HidBaseHandle::testDone = "testDone";
const QString HidBaseHandle::testReady = "testReady";
HidBaseHandle::HidBaseHandle()
{
    writeData_T_hid = [=](hid_device *hid_handle, const int& deviceID, unsigned char *pdata, size_t length){
            unsigned char *data = new unsigned char[10+length];
            seq++;
            data[1] = deviceID & 0xFF;
            data[2] = (deviceID >> 8) & 0xFF;
            data[3] = (deviceID >> 16) & 0xFF;
            data[4] = (deviceID >> 24) & 0xFF;
            data[5] = seq & 0xFF;
            data[6] = (seq >> 8) & 0xFF;
            data[7] = 12;
            memcpy(&data[8], pdata, length);
            unsigned short crc = crc16_ccitt(0, data + 1, sizeof(data) - 3);
            data[10+length - 1] = (crc >> 8) & 0xFF;
            data[10+length - 2] = crc & 0xFF;
            hid_write(hid_handle, data, 10+length);
            delete [] data;
    };
}

void HidBaseHandle::send_anserkey_quesion(const int& deviceID, hid_device *hid_handle)
{
    unsigned char data[] = {0x01, 0x7F, 0x00, 0x0e, 0x14};
    writeData_T_hid(hid_handle, deviceID, data, sizeof (data));
}

void HidBaseHandle::send_write_quesion(const int& deviceID, hid_device *hid_handle)
{
    unsigned char data[] = {0x01, 0x7f, 0x02, 0x0e, 0x14};
    writeData_T_hid(hid_handle, deviceID, data, sizeof (data));
}

void HidBaseHandle::send_audio_quesion(const int &deviceID, hid_device *hid_handle)
{
    unsigned char data[] = {0x01, 0x0, 0x11, 0x00, 0x01};
    writeData_T_hid(hid_handle, deviceID, data, sizeof (data));
}

void HidBaseHandle::send_motor_action(const int &deviceID, hid_device *hid_handle)
{
    unsigned char data[] = {0x05, 0x0, 0x01, 0x64, 0x64};
    writeData_T_hid(hid_handle, deviceID, data, sizeof (data));
}

void HidBaseHandle::send_beep_action(const int &deviceID, hid_device *hid_handle)
{
    unsigned char data[] = {0x04, 0x0, 0x01, 0x64, 0x64};
    writeData_T_hid(hid_handle, deviceID, data, sizeof (data));
}

void HidBaseHandle::send_led_action(const int &deviceID, hid_device *hid_handle)
{
    unsigned char data[] = {0x03, 0x0, 0x01, 0x64, 0x64, 0x00, 0x00, 0x00};
    writeData_T_hid(hid_handle, deviceID, data, sizeof (data));
}

void HidBaseHandle::send_show_message(const int &deviceID, QByteArray message, hid_device *hid_handle)
{
    char data[49] = {0};
    data[0]=0x02;
    strcpy(&data[1], message.data());
    writeData_T_hid(hid_handle, deviceID, reinterpret_cast<unsigned char *>(data), sizeof (data));
}
hid_device* HidBaseHandle::openHid_untillopened(void)
{
    hid_device *hid_handle = nullptr;
    forever {
        hid_handle = hid_open(0x0483, 0x5750, nullptr);
        if (hid_handle  != nullptr) {
            break;
        }
    }
    return hid_handle;
}
