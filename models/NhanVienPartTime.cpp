#include "NhanVienPartTime.h"
#include <iostream>

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
    std::cout << " -> Luong/Gio: " << luongTheoGio << " | PartTime" << std::endl;
}

std::string NhanVienPartTime::serialize() const {
    return NhanVien::serialize() + "|" + std::to_string(luongTheoGio);
}
