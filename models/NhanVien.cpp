#include "NhanVien.h"
#include <iostream>
#include <iomanip>
#include <sstream>

static std::string formatDouble(double val, int precision = 2) {
    std::ostringstream out;
    out << std::fixed << std::setprecision(precision) << val;
    return out.str();
}

NhanVien::NhanVien() : luongCoBan(0) {}

NhanVien::NhanVien(std::string maNV, std::string hoTen, std::string ngaySinh, std::string gioiTinh,
                   std::string soDienThoai, std::string email, std::string diaChi,
                   std::string maPB, std::string chucVu, std::string loaiNV, double luongCoBan)
    : maNV(maNV), hoTen(hoTen), ngaySinh(ngaySinh), gioiTinh(gioiTinh),
      soDienThoai(soDienThoai), email(email), diaChi(diaChi),
      maPB(maPB), chucVu(chucVu), loaiNV(loaiNV), luongCoBan(luongCoBan) {}

NhanVien::~NhanVien() {}

std::string NhanVien::getMaNV() const { return maNV; }
std::string NhanVien::getHoTen() const { return hoTen; }
std::string NhanVien::getLoaiNV() const { return loaiNV; }
double NhanVien::getLuongCoBan() const { return luongCoBan; }
std::string NhanVien::getMaPB() const { return maPB; }

void NhanVien::setMaNV(std::string maNV) { this->maNV = maNV; }
void NhanVien::setHoTen(std::string hoTen) { this->hoTen = hoTen; }
void NhanVien::setLuongCoBan(double luongCoBan) { this->luongCoBan = luongCoBan; }
void NhanVien::setMaPB(std::string maPB) { this->maPB = maPB; }

void NhanVien::hienThiThongTin() const {
    std::cout << std::left << std::setw(10) << maNV
              << std::setw(25) << hoTen
              << std::setw(12) << loaiNV
              << std::right << std::setw(15) << std::fixed << std::setprecision(2) << luongCoBan
              << "  " << std::left << std::setw(10) << maPB;
}

std::string NhanVien::serialize() const {
    return maNV + "|" + hoTen + "|" + ngaySinh + "|" + gioiTinh + "|" +
           soDienThoai + "|" + email + "|" + diaChi + "|" + maPB + "|" +
           chucVu + "|" + loaiNV + "|" + formatDouble(luongCoBan);
}
