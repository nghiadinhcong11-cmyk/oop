#include "NhanVienFullTime.h"
#include <iostream>
#include <iomanip>

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
    std::cout << " -> Phu cap: " << phuCap << " | FullTime" << std::endl;
}

double NhanVienFullTime::getPhuCap() const { return phuCap; }
double NhanVienFullTime::getTienTangCa(const ChamCong& cc) const {
    return cc.getSoGioTangCa() * 150000;
}

std::string NhanVienFullTime::serialize() const {
    return NhanVien::serialize() + "|" + std::to_string(phuCap);
}

void NhanVienFullTime::setPhuCap(double phuCap) { this->phuCap = phuCap; }
double NhanVienFullTime::getTienTangCa() const { return tienTangCa; }
void NhanVienFullTime::setTienTangCa(double tienTangCa) { this->tienTangCa = tienTangCa; }
