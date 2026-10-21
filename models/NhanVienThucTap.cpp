#include "NhanVienThucTap.h"
#include <iostream>
using namespace std;

NhanVienThucTap::NhanVienThucTap() : NhanVien(), troCap(0) {
    this->loaiNV = "Intern";
}

NhanVienThucTap::NhanVienThucTap(string maNV, string hoTen, string ngaySinh, string gioiTinh,
                                 string soDienThoai, string email, string diaChi,
                                 string maPB, string chucVu, string ngayVaoLam, double luongCoBan,
                                 double troCap)
    : NhanVien(maNV, hoTen, ngaySinh, gioiTinh, soDienThoai, email, diaChi, maPB, chucVu, ngayVaoLam, "Intern", luongCoBan),
      troCap(troCap) {}

double NhanVienThucTap::getLuongGoc() const {
    return troCap;
}

double NhanVienThucTap::getLuongCoBan(const ChamCong& cc) const {
    // Tinh theo gio (8h/ngay), tro cap o đây đóng vai trò là lương theo giờ
    return cc.getSoNgayCong() * 8 * troCap;
}

double NhanVienThucTap::tinhLuong(const ChamCong& cc) const {
    return getLuongCoBan(cc);
}

double NhanVienThucTap::getPhuCap() const {
    return troCap;
}

void NhanVienThucTap::hienThiThongTin() const {
    NhanVien::hienThiThongTin();
    cout << (to_string(troCap) + " (tro cap/gio)") << endl;
}

void NhanVienThucTap::hienThiChiTiet() const {
    NhanVien::hienThiChiTiet();
    cout << "Tro cap:        " << troCap << endl;
    cout << "---------------------------------" << endl;
}

string NhanVienThucTap::taoDongDuLieu() const {
    return NhanVien::taoDongDuLieu() + "|" + to_string(troCap);
}
