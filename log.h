#pragma once


#include <cstdio>
#include <sstream>
#include <string>

#define LOG(level) \
    XFiberLog::instance().log(__FILE__, __LINE__, __FUNCTION__, __DATE__, __TIME__,level)


class XFiberLog{
public:
    // XFiberLog(const char* file, int line,const char* function, const char* date, const char* time,std::string level) {
    //     stream_ <<"["<<level<<"][" << date << " " << time << "][" << file <<" - " << function << ":" << line << "]";
    // }
    static XFiberLog& instance(){
        static XFiberLog log;
        return log;
    }
    ~XFiberLog() {
        // stream_ << std::endl;
        // std::string str_newline(stream_.str());
        // fprintf(stderr, "%s", str_newline.c_str());
        // fflush(stderr);
    }
    std::ostream& log(const char *file, int line, const char *function, const char *date, const char *time, std::string level)
    {
         return stream_ << "[" << level << "][" << date << " " << time << "][" << file << " - " << function << ":" << line << "]";
    }

    std::ostream& stream() { return stream_;}



    std::ostringstream stream_;
};