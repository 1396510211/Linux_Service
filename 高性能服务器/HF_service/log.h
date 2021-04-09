#pragma once
#include <string>
#include <stdint.h>
#include <vector>
#include <memory>
#include <list>
#include <sstream>
#include <fstream>

namespace haifeng {
//日志事件
class LogEvent
{
public:
	typedef std::shared_ptr<LogEvent> ptr;
	LogEvent();
	
private:
	const char* m_file = nullptr;  	//文件名
	uint32_t m_line = 0;			//行号
	uint32_t m_elpse = 0;			//程序启动到现在的运行毫秒数
	uint32_t m_threadID = 0; 		//线程号
	uint32_t m_fiberdID = 0;		//协程号
	uint64_t m_time = 0;			//时间戳
	std::string m_content;			
};
//日志级别
class LogLevel{
public:
	enum Level {
		DEBUG = 0,
		INFO = 1,
		WARN = 2,
		ERROR = 3,
		FATAL = 4,
	};
};
//日志格式器
class LogFormatter{
public:
	typedef std::shared_ptr<LogFormatter> ptr;
	LogFormatter(const std::string& pattern);
	void init();
	std::string format(LogEvent::ptr event);
private:
	class FormatItem{
	public:
		typedef std::shared_ptr<FormatItem> ptr;
		virtual ~FormatItem();
		virtual void format(std::ostream &os,LogEvent::ptr enent) = 0;
	};
private:
	std::string m_pattren;
	std::vector<FormatItem::ptr> m_items;
};
//日志输出地
class LogAppender
{
public:
	typedef std::shared_ptr<LogAppender> ptr;
	LogAppender();
	virtual ~LogAppender();
	virtual void log(LogLevel::Level level , LogEvent::ptr event) = 0;
	void setFomatter(LogFormatter::ptr val){ m_formatter=val; }
	LogFormatter::ptr getFomatter() const { return m_formatter; }
protected:
	LogLevel::Level m_level;
	LogFormatter::ptr m_formatter;
};

//日志器
class Logger
{
public:
	typedef std::shared_ptr<Logger> ptr;
	Logger(const std::string & name="root");
	void log(LogLevel::Level level , LogEvent::ptr event);

	void debug(LogEvent::ptr event);
	void info(LogEvent::ptr event);
	void warn(LogEvent::ptr event);
	void error(LogEvent::ptr event);
	void fatal(LogEvent::ptr event);

	void addAppender(LogAppender::ptr appender);
	void delAppender(LogAppender::ptr appender);
	LogLevel::Level getLever () const { return m_level;}
	void setLever(LogLevel::Level val){ m_level=val;}

private:
	LogLevel::Level m_level;					//日志级别
	std::string m_name;  						//日志名称
	std::list<LogAppender::ptr> m_Appenders; 	//Appender集合; 			
	 
};

//输出到控制台的Appender
class StdoutLogAppender:public LogAppender{
public:
	typedef std::shared_ptr<StdoutLogAppender> ptr;
	void log(LogLevel::Level level , LogEvent::ptr event) override;	
private:

};
//输出到文件的Appender
class FileLogAppender :public LogAppender{
public:
	typedef std::shared_ptr<FileLogAppender> ptr;
	FileLogAppender(const std::string filename);
	void log(LogLevel::Level level , LogEvent::ptr event) override;
	bool reopen();
private:
	std::string m_filename;
	std::ofstream m_filestream;

};

}