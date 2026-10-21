#ifndef CHAMCONG_H
#define CHAMCONG_H

#include <string>

using namespace std;

class ChamCong {
private:
    string maCC;
    string maNV;
    int thang;
    int nam;
    double soNgayCong;
    double soGioTangCa;

public:
    ChamCong();
    ChamCong(string maCC, string maNV, int thang, int nam, double soNgayCong, double soGioTangCa);

    // Getters
    string getMaCC() const;
    string getMaNV() const;
    int getThang() const;
    int getNam() const;
    double getSoNgayCong() const;
    double getSoGioTangCa() const;

    // Setters với validation cơ bản
    void setThang(int t);
    void setSoNgayCong(double snc);
    void setSoGioTangCa(double sgtc);

    string taoDongDuLieu() const;
};

#endif // CHAMCONG_H
