#ifndef HIDBASEHANDLE_H
#define HIDBASEHANDLE_H
#include "QString"
#include "functional"
#include "hidapi.h"

class HidBaseHandle
{
public:
    const static QString keyA;
    const static QString keyB;
    const static QString keyC;
    const static QString keyD;
    const static QString keyT;
    const static QString keyF;
    const static QString keyG;
    const static QString keyPress;
    const static QString testDone;
    const static QString testReady;
    HidBaseHandle();
    void send_anserkey_quesion(const int& deviceID, hid_device *hid_handle);
    void send_write_quesion(const int& deviceID, hid_device *hid_handle);
    void send_audio_quesion(const int& deviceID, hid_device *hid_handle);
    void send_motor_action(const int& deviceID, hid_device *hid_handle);
    void send_beep_action(const int& deviceID, hid_device *hid_handle);
    void send_led_action(const int& deviceID, hid_device *hid_handle);
    void send_show_message(const int& deviceID, QByteArray message, hid_device *hid_handle);
    hid_device *openHid_untillopened();
    void hidClose(hid_device *handle){hid_close(handle);}
    virtual void ansStatusHandle(QByteArray& data)=0;
private:
    int seq=0;
    std::function<void(hid_device *, const int&, unsigned char*, size_t)>writeData_T_hid;

};

#endif // HIDBASEHANDLE_H
