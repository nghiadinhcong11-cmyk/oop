#include "NhanVienFullTime.h"
#include <iostream>
using namespace std;

NhanVienFullTime::NhanVienFullTime() : NhanVien(), phuCap(0), tienTangCa(0) {
    this->loaiNV = "Full-time";
}

NhanVienFullTime::NhanVienFullTime(string maNV, string hoTen, string ngaySinh, string gioiTinh,
                                   string soDienThoai, string email, string diaChi,
                                   string maPB, string chucVu, string ngayVaoLam, double luongCoBan,
                                   double phuCap, double tienTangCa)
    : NhanVien(maNV, hoTen, ngaySinh, gioiTinh, soDienThoai, email, diaChi, maPB, chucVu, ngayVaoLam, "Full-time", luongCoBan),
      phuCap(phuCap), tienTangCa(tienTangCa) {}

double NhanVienFullTime::getLuongGoc() const {
    return luongCoBan;
}

double NhanVienFullTime::getLuongCoBan(const ChamCong& cc) const {
    double luongCBThucTe = luongCoBan;
    if (cc.getSoNgayCong() < 24) {
        double soNgayThieu = 24 - cc.getSoNgayCong();
        luongCBThucTe -= soNgayThieu * 100000;
    }
    if (luongCBThucTe > 0) {
        return luongCBThucTe;
    }
    return 0;
}

double NhanVienFullTime::tinhLuong(const ChamCong& cc) const {
    return getLuongCoBan(cc) + phuCap + getTienTangCa(cc);
}

void NhanVienFullTime::hienThiThongTin() const {
    NhanVien::hienThiThongTin();
    cout << (to_string(phuCap) + " (phu cap/thang)") << endl;
}

void NhanVienFullTime::hienThiChiTiet() const {
    NhanVien::hienThiChiTiet();
    cout << "Phu cap:        " << phuCap << endl;
    cout << "---------------------------------" << endl;
}

double NhanVienFullTime::getPhuCap() const { return phuCap; }
double NhanVienFullTime::getTienTangCa(const ChamCong& cc) const {
    // Luong tang ca Full-time tam thoi de muc co dinh 150k/h hoac co the tinh theo cong thuc khac
    return cc.getSoGioTangCa() * 150000;
}

string NhanVienFullTime::taoDongDuLieu() const {
    return NhanVien::taoDongDuLieu() + "|" + to_string(phuCap);
}

void NhanVienFullTime::setPhuCap(double phuCap) { this->phuCap = phuCap; }
double NhanVienFullTime::getTienTangCa() const { return tienTangCa; }
void NhanVienFullTime::setTienTangCa(double tienTangCa) { this->tienTangCa = tienTangCa; }
