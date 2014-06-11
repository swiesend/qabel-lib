#include "qbl-pipe.h"
#include "encoding/qbl-base64.h"

QblPipe::QblPipe()
{
}

QblPipe::~QblPipe()
{

}

void QblPipe::onFinish()
{
}

void QblPipe::setListener(QblPipeListener* listener)
{
    this->listener = listener;
}

void QblPipe::onData(const std::vector<char> &data)
{
    this->buffer->insert(this->buffer->end(), data.begin(), data.end());
}

std::string* QblPipe::create(const std::string &data)
{
    this->listener = this;
    this->buffer = new std::vector<char>;
    this->pushStr(data);
    this->finish();

    std::string *tmp = new std::string(buffer->begin(), buffer->end());
    this->buffer = NULL;
    this->listener = NULL;

    return (tmp);
}

std::vector<char>* QblPipe::create(const std::vector<char> &data)
{
    std::vector<char> *tmp;

    this->listener = this;
    this->buffer = new std::vector<char>;
    this->push(data);
    this->finish();

    tmp = buffer;
    this->buffer = NULL;
    this->listener = NULL;

    return (tmp);
}

QblPipeListener* QblPipe::getListener()
{
    return (this->listener);
}

void QblPipe::pushStr(const std::string &data)
{
    *this << data;
}

void QblPipe::operator<<(const std::vector<char> &data)
{
    this->push(data);
}

void QblPipe::operator<<(const std::string &str)
{
    this->push(std::vector<char>(str.begin(), str.end()));
}

void QblPipe::operator<<(const char *str)
{
    this->push(std::vector<char>(str, str + strlen(str)));
}

void QblPipe::operator<<(std::ifstream &in)
{
    std::stringstream buffer;
    buffer << in.rdbuf();

    std::string content(buffer.str());

    this->pushStr(content);
}
