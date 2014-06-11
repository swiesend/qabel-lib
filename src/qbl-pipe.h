#ifndef __QBL_PIPE_H__
#define __QBL_PIPE_H__

#include <string>
#include <cstddef>
#include <vector>
#include <cstring>
#include <sstream>
#include <fstream>

class QblPipeListener {
public:
    QblPipeListener(){};
    virtual ~QblPipeListener(){};
    virtual void onData(const std::vector<char> &data) = 0;
    virtual void onFinish() = 0;
};

/**
 * @todo: find a description.
 */
class QblPipe : private QblPipeListener {

public:
    /**
     * Constructor
     */
    QblPipe();

    /**
     * Destructor
     */
    virtual ~QblPipe();

    void setListener(QblPipeListener* listener);

    QblPipeListener* getListener();

    void pushStr(const std::string &data);

    virtual void push(const std::vector<char> &data) = 0;

    virtual void finish() = 0;

    virtual void onData(const std::vector<char> &data);

    std::string* create(const std::string &data);

    std::vector<char>* create(const std::vector<char> &data);

    virtual void onFinish();

    void operator<<(const std::vector<char> &data);

    void operator<<(const std::string &str);

    void operator<<(const char *str);

    void operator<<(std::ifstream &in);

private:
    QblPipeListener *listener = nullptr;
    std::vector<char> *buffer = nullptr;
};

#endif
