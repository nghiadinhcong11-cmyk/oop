#include "NhanVien.h"
#include <iostream>
#include <iomanip>

using namespace std;

NhanVien::NhanVien() : luongCoBan(0) {}

NhanVien::NhanVien(string maNV, string hoTen, string ngaySinh, string gioiTinh,
                   string soDienThoai, string email, string diaChi,
                   string maPB, string chucVu, string ngayVaoLam, string loaiNV, double luongCoBan)
    : maNV(maNV), hoTen(hoTen), ngaySinh(ngaySinh), gioiTinh(gioiTinh),
      soDienThoai(soDienThoai), email(email), diaChi(diaChi),
      maPB(maPB), chucVu(chucVu), ngayVaoLam(ngayVaoLam), loaiNV(loaiNV), luongCoBan(luongCoBan) {}

NhanVien::~NhanVien() {}

string NhanVien::getMaNV() const { return maNV; }
string NhanVien::getHoTen() const { return hoTen; }
string NhanVien::getLoaiNV() const { return loaiNV; }
string NhanVien::getNgaySinh() const { return ngaySinh; }
string NhanVien::getGioiTinh() const { return gioiTinh; }
string NhanVien::getSoDienThoai() const { return soDienThoai; }
string NhanVien::getEmail() const { return email; }
string NhanVien::getDiaChi() const { return diaChi; }
string NhanVien::getMaPB() const { return maPB; }
string NhanVien::getNgayVaoLam() const { return ngayVaoLam; }
string NhanVien::getChucVu() const { return chucVu; }

void NhanVien::setMaNV(string maNV) { this->maNV = maNV; }
void NhanVien::setHoTen(string hoTen) { this->hoTen = hoTen; }
void NhanVien::setNgaySinh(string ngaySinh) { this->ngaySinh = ngaySinh; }
void NhanVien::setGioiTinh(string gioiTinh) { this->gioiTinh = gioiTinh; }
void NhanVien::setSoDienThoai(string soDienThoai) { this->soDienThoai = soDienThoai; }
void NhanVien::setEmail(string email) { this->email = email; }
void NhanVien::setDiaChi(string diaChi) { this->diaChi = diaChi; }
void NhanVien::setChucVu(string chucVu) { this->chucVu = chucVu; }
void NhanVien::setNgayVaoLam(string ngayVaoLam) { this->ngayVaoLam = ngayVaoLam; }
void NhanVien::setLuongCoBan(double luongCoBan) { this->luongCoBan = luongCoBan; }
void NhanVien::setMaPB(string maPB) { this->maPB = maPB; }

void NhanVien::hienThiThongTin() const {
    cout << fixed << setprecision(0);
    // Cac lop dan xuat noi cot dac thu vao sau cot chung cuoi cung.
    // Giu nguyen thu tu va do rong nay de moi loai nhan vien thang cot.
    cout << maNV << " | "
              << hoTen << " | "
              << ngaySinh << " | "
              << gioiTinh << " | "
              << soDienThoai << " | "
              << email << " | "
              << diaChi << " | "
              << maPB << " | "
              << chucVu << " | "
              << ngayVaoLam << " | "
              << loaiNV << " | "
              << luongCoBan
              << " | ";
}

void NhanVien::hienThiChiTiet() const {
    cout << fixed << setprecision(0);
    cout << "\n--- CHI TIET NHAN VIEN: " << maNV << " ---" << endl;
    cout << "Ho ten:         " << hoTen << endl;
    cout << "Ngay sinh:      " << ngaySinh << endl;
    cout << "Gioi tinh:      " << gioiTinh << endl;
    cout << "So dien thoai:  " << soDienThoai << endl;
    cout << "Email:          " << email << endl;
    cout << "Dia chi:        " << diaChi << endl;
    cout << "Phong ban:      " << maPB << endl;
    cout << "Chuc vu:        " << chucVu << endl;
    cout << "Ngay vao lam:   " << ngayVaoLam << endl;
    cout << "Loai nhan vien: " << loaiNV << endl;
    cout << "Luong co ban:   " << luongCoBan << endl;
}

string NhanVien::taoDongDuLieu() const {
    return maNV + "|" + hoTen + "|" + ngaySinh + "|" + gioiTinh + "|" +
           soDienThoai + "|" + email + "|" + diaChi + "|" + maPB + "|" +
           chucVu + "|" + ngayVaoLam + "|" + loaiNV + "|" + to_string(luongCoBan);
}
