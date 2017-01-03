#ifndef MEASUREMENT_HPP_
#define MEASUREMENT_HPP_

class Measurement {
public:
    Measurement(int data, char* sensorKeyword);
    virtual ~Measurement();

    int getData() const;
    void setData(int data);

    char* getSensorKeyword() const;
    void setSensorKeyword(char* sensorKeyword);

private:
    int _data;
    char* _sensorKeyword;
};

#endif // MEASUREMENT_HPP_
