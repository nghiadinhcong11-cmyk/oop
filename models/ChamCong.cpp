#include "ChamCong.h"
using namespace std;

ChamCong::ChamCong() : thang(1), nam(2024), soNgayCong(0), soGioTangCa(0) {}

ChamCong::ChamCong(string maCC, string maNV, int thang, int nam, double soNgayCong, double soGioTangCa)
    : maCC(maCC), maNV(maNV), thang(thang), nam(nam), soNgayCong(soNgayCong), soGioTangCa(soGioTangCa) {}

string ChamCong::getMaCC() const { return maCC; }
string ChamCong::getMaNV() const { return maNV; }
int ChamCong::getThang() const { return thang; }
int ChamCong::getNam() const { return nam; }
double ChamCong::getSoNgayCong() const { return soNgayCong; }
double ChamCong::getSoGioTangCa() const { return soGioTangCa; }

void ChamCong::setThang(int t) { if (t >= 1 && t <= 12) thang = t; }
void ChamCong::setSoNgayCong(double snc) { if (snc >= 0) soNgayCong = snc; }
void ChamCong::setSoGioTangCa(double sgtc) { if (sgtc >= 0) soGioTangCa = sgtc; }

string ChamCong::taoDongDuLieu() const {
    return maCC + "|" + maNV + "|" + to_string(thang) + "|" + to_string(nam) + "|" +
           to_string(soNgayCong) + "|" + to_string(soGioTangCa);
}
