#ifndef CHAMCONG_H
#define CHAMCONG_H

#include <string>

class ChamCong {
private:
    std::string maCC;
    std::string maNV;
    int thang;
    int nam;
    double soNgayCong;
    double soGioTangCa;

public:
    ChamCong();
    ChamCong(std::string maCC, std::string maNV, int thang, int nam, double soNgayCong, double soGioTangCa);

    // Getters
    std::string getMaCC() const;
    std::string getMaNV() const;
    int getThang() const;
    int getNam() const;
    double getSoNgayCong() const;
    double getSoGioTangCa() const;

    // Setters với validation cơ bản
    void setThang(int t);
    void setSoNgayCong(double snc);
    void setSoGioTangCa(double sgtc);

    std::string serialize() const;
};

#endif // CHAMCONG_H
