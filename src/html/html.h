#ifndef HTML_H
#define HTML_H

#include <WString.h>

class setJsonData {
    public:
        static String data(const String& waterLevel, const String& msg, const String& timeStamp, const String& nameOfEsp, const String& fwVersion);
        static String page;
};

#endif // HTML_H