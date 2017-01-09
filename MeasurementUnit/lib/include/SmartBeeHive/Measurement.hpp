#ifndef MEASUREMENT_HPP_
#define MEASUREMENT_HPP_

class Measurement {
public:
    Measurement(int data, char* type, int id);
    virtual ~Measurement();

    int getData() const;
    void setData(int data);

    char* getType() const;
    void setType(char* type);

    int getId() const;
    void setId(int id);

private:
    int _data;
    char* _type;
    int _id;
};

#endif // MEASUREMENT_HPP_
