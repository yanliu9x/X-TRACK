#include "HAL.h"
#include "TinyGPSPlus/src/TinyGPS++.h"

#define GNSS_SERIAL             CONFIG_GNSS_SERIAL
#define DEBUG_SERIAL            CONFIG_DEBUG_SERIAL
#define GNSS_USE_TRANSPARENT    CONFIG_GNSS_USE_TRANSPARENT

static TinyGPSPlus gnss;

void HAL::GNSS_Init()
{
    GNSS_SERIAL.begin(CONFIG_GNSS_BAUD_RATE);

    Serial.print("GNSS: TinyGPS++ library v. ");
    Serial.print(TinyGPSPlus::libraryVersion());
    Serial.println(" by Mikal Hart");
}

void HAL::GNSS_Update()
{
#if CONFIG_GNSS_BUF_OVERLOAD_CHK && !GNSS_USE_TRANSPARENT
    int available = GNSS_SERIAL.available();
    DEBUG_SERIAL.printf("GNSS: Buffer available = %d", available);
    if(available >= SERIAL_RX_BUFFER_SIZE / 2)
    {
        DEBUG_SERIAL.print(", maybe overload!");
    }
    DEBUG_SERIAL.println();
#endif

    while (GNSS_SERIAL.available() > 0)
    {
        char c = GNSS_SERIAL.read();
#if GNSS_USE_TRANSPARENT
        DEBUG_SERIAL.write(c);
#endif
        gnss.encode(c);
    }

#if GNSS_USE_TRANSPARENT
    while (DEBUG_SERIAL.available() > 0)
    {
        GNSS_SERIAL.write(DEBUG_SERIAL.read());
    }
#endif
}

bool HAL::GNSS_GetInfo(GNSS_Info_t* info)
{
    memset(info, 0, sizeof(GNSS_Info_t));

    info->isVaild = gnss.location.isValid();
    info->longitude = gnss.location.lng();
    info->latitude = gnss.location.lat();
    info->altitude = gnss.altitude.meters();
    info->speed = gnss.speed.kmph();
    info->course = gnss.course.deg();

    info->clock.year = gnss.date.year();
    info->clock.month = gnss.date.month();
    info->clock.day = gnss.date.day();
    info->clock.hour = gnss.time.hour();
    info->clock.minute = gnss.time.minute();
    info->clock.second = gnss.time.second();
    info->satellites = gnss.satellites.value();

    return info->isVaild;
}

bool HAL::GNSS_LocationIsValid()
{
    return gnss.location.isValid();
}

double HAL::GNSS_GetDistanceOffset(GNSS_Info_t* info, double preLong, double preLat)
{
    return gnss.distanceBetween(info->latitude, info->longitude, preLat, preLong);
}
