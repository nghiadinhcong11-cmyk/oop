#include "NhanVienPartTime.h"
#include <iostream>
#include <iomanip>
#include <sstream>

static std::string formatDouble(double val, int precision = 2) {
    std::ostringstream out;
    out << std::fixed << std::setprecision(precision) << val;
    return out.str();
}

NhanVienPartTime::NhanVienPartTime() : NhanVien(), luongTheoGio(0) {
    this->loaiNV = "PartTime";
}

NhanVienPartTime::NhanVienPartTime(std::string maNV, std::string hoTen, std::string ngaySinh, std::string gioiTinh,
                                   std::string soDienThoai, std::string email, std::string diaChi,
                                   std::string maPB, std::string chucVu, double luongCoBan,
                                   double luongTheoGio)
    : NhanVien(maNV, hoTen, ngaySinh, gioiTinh, soDienThoai, email, diaChi, maPB, chucVu, "PartTime", luongCoBan),
      luongTheoGio(luongTheoGio) {}

double NhanVienPartTime::tinhLuong(const ChamCong& cc) const {
    return (cc.getSoNgayCong() * 8 * luongTheoGio) + getTienTangCa(cc);
}

double NhanVienPartTime::getTienTangCa(const ChamCong& cc) const {
    return cc.getSoGioTangCa() * luongTheoGio * 1.5;
}

void NhanVienPartTime::hienThiThongTin() const {
    NhanVien::hienThiThongTin();
    std::cout << "  " << std::right << std::setw(15) << std::fixed << std::setprecision(2) << luongTheoGio << " (L/h)" << std::endl;
}

std::string NhanVienPartTime::serialize() const {
    return NhanVien::serialize() + "|" + formatDouble(luongTheoGio);
}
