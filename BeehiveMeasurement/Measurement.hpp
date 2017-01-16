#ifndef MEASUREMENT_HPP_
#define MEASUREMENT_HPP_

class Measurement {
public:
    Measurement(double data, char* type, int id);
    virtual ~Measurement();

    double getData() const;
    void setData(double data);

    char* getType() const;
    void setType(char* type);

    int getId() const;
    void setId(int id);

private:
    double _data;
    char* _type;
    int _id;
};

#endif // MEASUREMENT_HPP_
