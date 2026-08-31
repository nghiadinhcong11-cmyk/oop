#include "NhanVienThucTap.h"
#include <iostream>

NhanVienThucTap::NhanVienThucTap() : NhanVien(), troCap(0) {
    this->loaiNV = "ThucTap";
}

NhanVienThucTap::NhanVienThucTap(std::string maNV, std::string hoTen, std::string ngaySinh, std::string gioiTinh,
                                 std::string soDienThoai, std::string email, std::string diaChi,
                                 std::string maPB, std::string chucVu, double luongCoBan,
                                 double troCap)
    : NhanVien(maNV, hoTen, ngaySinh, gioiTinh, soDienThoai, email, diaChi, maPB, chucVu, "ThucTap", luongCoBan),
      troCap(troCap) {}

double NhanVienThucTap::tinhLuong(const ChamCong& cc) const {
    return troCap;
}

double NhanVienThucTap::getPhuCap() const {
    return troCap;
}

void NhanVienThucTap::hienThiThongTin() const {
    NhanVien::hienThiThongTin();
    std::cout << " -> Tro cap: " << troCap << " | ThucTap" << std::endl;
}

std::string NhanVienThucTap::serialize() const {
    return NhanVien::serialize() + "|" + std::to_string(troCap);
}
