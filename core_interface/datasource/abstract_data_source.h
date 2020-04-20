#ifndef ABSTRACTDATASOURCE_H
#define ABSTRACTDATASOURCE_H

enum struct Status:unsigned char{
    Initial,
    Ready,
    Start,
    Running,
    Done,
    Over
};

template <typename InputDataType>
class AbstractDataSource
{
public:
    explicit AbstractDataSource();

    virtual ~AbstractDataSource();

    virtual void doWork(const InputDataType &)=0;

    virtual Status status()=0;

protected:

    virtual void setInput()=0;

    virtual void generateRandomData()=0;

};

#endif // ABSTRACTDATASOURCE_H
