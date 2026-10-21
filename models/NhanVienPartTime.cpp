#include "NhanVienPartTime.h"
#include <iostream>
using namespace std;

NhanVienPartTime::NhanVienPartTime() : NhanVien(), luongTheoGio(0) {
    this->loaiNV = "Part-time";
}

NhanVienPartTime::NhanVienPartTime(string maNV, string hoTen, string ngaySinh, string gioiTinh,
                                   string soDienThoai, string email, string diaChi,
                                   string maPB, string chucVu, string ngayVaoLam, double luongCoBan,
                                   double luongTheoGio)
    : NhanVien(maNV, hoTen, ngaySinh, gioiTinh, soDienThoai, email, diaChi, maPB, chucVu, ngayVaoLam, "Part-time", luongCoBan),
      luongTheoGio(luongTheoGio) {}

double NhanVienPartTime::getLuongGoc() const {
    return luongTheoGio;
}

double NhanVienPartTime::getLuongCoBan(const ChamCong& cc) const {
    // Luong tinh theo gio cho PartTime: (Số ngày công * 8 * Mức lương giờ)
    return cc.getSoNgayCong() * 8 * luongTheoGio;
}

double NhanVienPartTime::tinhLuong(const ChamCong& cc) const {
    return getLuongCoBan(cc) + getTienTangCa(cc);
}

double NhanVienPartTime::getTienTangCa(const ChamCong& cc) const {
    return cc.getSoGioTangCa() * luongTheoGio * 1.5;
}

void NhanVienPartTime::hienThiThongTin() const {
    NhanVien::hienThiThongTin();
    cout << (to_string(luongTheoGio) + " (luong/gio)") << endl;
}

void NhanVienPartTime::hienThiChiTiet() const {
    NhanVien::hienThiChiTiet();
    cout << "Luong theo gio: " << luongTheoGio << endl;
    cout << "---------------------------------" << endl;
}

string NhanVienPartTime::taoDongDuLieu() const {
    return NhanVien::taoDongDuLieu() + "|" + to_string(luongTheoGio);
}
