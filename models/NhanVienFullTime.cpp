#include "NhanVienFullTime.h"
#include <iostream>
#include <iomanip>
#include <sstream>

static std::string formatDouble(double val, int precision = 2) {
    std::ostringstream out;
    out << std::fixed << std::setprecision(precision) << val;
    return out.str();
}

NhanVienFullTime::NhanVienFullTime() : NhanVien(), phuCap(0), tienTangCa(0) {
    this->loaiNV = "FullTime";
}

NhanVienFullTime::NhanVienFullTime(std::string maNV, std::string hoTen, std::string ngaySinh, std::string gioiTinh,
                                   std::string soDienThoai, std::string email, std::string diaChi,
                                   std::string maPB, std::string chucVu, double luongCoBan,
                                   double phuCap, double tienTangCa)
    : NhanVien(maNV, hoTen, ngaySinh, gioiTinh, soDienThoai, email, diaChi, maPB, chucVu, "FullTime", luongCoBan),
      phuCap(phuCap), tienTangCa(tienTangCa) {}

double NhanVienFullTime::tinhLuong(const ChamCong& cc) const {
    return luongCoBan + phuCap + (cc.getSoGioTangCa() * 150000);
}

void NhanVienFullTime::hienThiThongTin() const {
    NhanVien::hienThiThongTin();
    std::cout << "  " << std::right << std::setw(15) << std::fixed << std::setprecision(2) << phuCap << std::endl;
}

double NhanVienFullTime::getPhuCap() const { return phuCap; }
double NhanVienFullTime::getTienTangCa(const ChamCong& cc) const {
    return cc.getSoGioTangCa() * 150000;
}

std::string NhanVienFullTime::serialize() const {
    return NhanVien::serialize() + "|" + formatDouble(phuCap);
}

void NhanVienFullTime::setPhuCap(double phuCap) { this->phuCap = phuCap; }
double NhanVienFullTime::getTienTangCa() const { return tienTangCa; }
void NhanVienFullTime::setTienTangCa(double tienTangCa) { this->tienTangCa = tienTangCa; }
