#include "ChamCong.h"
#include <iomanip>
#include <sstream>

static std::string formatDouble(double val, int precision = 2) {
    std::ostringstream out;
    out << std::fixed << std::setprecision(precision) << val;
    return out.str();
}

ChamCong::ChamCong() : thang(1), nam(2024), soNgayCong(0), soGioTangCa(0) {}

ChamCong::ChamCong(std::string maCC, std::string maNV, int thang, int nam, double soNgayCong, double soGioTangCa)
    : maCC(maCC), maNV(maNV), thang(thang), nam(nam), soNgayCong(soNgayCong), soGioTangCa(soGioTangCa) {}

std::string ChamCong::getMaCC() const { return maCC; }
std::string ChamCong::getMaNV() const { return maNV; }
int ChamCong::getThang() const { return thang; }
int ChamCong::getNam() const { return nam; }
double ChamCong::getSoNgayCong() const { return soNgayCong; }
double ChamCong::getSoGioTangCa() const { return soGioTangCa; }

void ChamCong::setThang(int t) { if (t >= 1 && t <= 12) thang = t; }
void ChamCong::setSoNgayCong(double snc) { if (snc >= 0) soNgayCong = snc; }
void ChamCong::setSoGioTangCa(double sgtc) { if (sgtc >= 0) soGioTangCa = sgtc; }

std::string ChamCong::serialize() const {
    return maCC + "|" + maNV + "|" + std::to_string(thang) + "|" + std::to_string(nam) + "|" +
           formatDouble(soNgayCong) + "|" + formatDouble(soGioTangCa);
}
