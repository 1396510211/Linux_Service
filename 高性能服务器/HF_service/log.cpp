#include "log.h"
namespace haifeng {
    Logger::Logger(const std::string & name="root")
        :m_name(name){
    }
    void Logger::addAppender(LogAppender::ptr appender){
        m_Appenders.push_back(appender);
    }
	void Logger::delAppender(LogAppender::ptr appender){
        for(auto it=m_Appenders.begin();it!=m_Appenders.end();it++){
            if(*it==appender){
                m_Appenders.erase(it);
                break;
            }
        }
    }
	void Logger::log(LogLevel::Level level , LogEvent::ptr event){
        if(level>=m_level){
            for(auto &it:m_Appenders){
                it->log(level,event);
            }
        }   
    }

	void Logger::debug(LogEvent::ptr event){
        debug(LogLevel::DEBUG,event);
    }
	void Logger::info(LogEvent::ptr event){
        debug(LogLevel::DEBUG,event);
    }
	void Logger::warn(LogEvent::ptr event){
        debug(LogLevel::DEBUG,event);
    }
	void Logger::error(LogEvent::ptr event){
        debug(LogLevel::DEBUG,event);
    }
	void Logger::fatal(LogEvent::ptr event){
        debug(LogLevel::DEBUG,event);
    }

	FileLogAppender::FileLogAppender(const std::string filename)
        :m_filename(filename){
    }

	void FileLogAppender::log(LogLevel::Level level , LogEvent::ptr event) {
        if(level>=m_level)
            m_filestream<<m_fomatter.
    }
    bool FileLogAppender::reopen(){
        if(m_filestream){
            m_filestream.close();
        }
        m_filestream.open(m_filename);
        return !!m_filestream;
    }

    void StdoutLogAppender::log(LogLevel::Level level , LogEvent::ptr event){

    }
    
    void LogFormatter::init(){

    }
	std::string LogFormatter::format(LogEvent::ptr event){

    }


}


