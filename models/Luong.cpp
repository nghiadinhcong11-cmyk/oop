#include "Luong.h"
#include <iomanip>

using namespace std;

Luong::Luong() : thang(1), nam(2024), luongGoc(0), luongCoBan(0), phuCap(0), tienTangCa(0), khauTru(0), luongThucNhan(0) {}

Luong::Luong(string maLuong, string maNV, string loaiNV, int thang, int nam,
              double lg, double lcb, double pc, double ttc, double kt, double ltn)
    : maLuong(maLuong), maNV(maNV), loaiNV(loaiNV), thang(thang), nam(nam),
      luongGoc(lg), luongCoBan(lcb), phuCap(pc), tienTangCa(ttc), khauTru(kt), luongThucNhan(ltn) {}

void Luong::hienThiPhieuLuong() const {
    cout << fixed << setprecision(0);
    cout << "\n--- PHIEU LUONG: " << maLuong << " ---" << endl;
    cout << "Ma NV: " << maNV << " (" << loaiNV << ") | Thang: " << thang << "/" << nam << endl;


    if (loaiNV == "FullTime" || loaiNV == "Full-time") {
        cout << "Luong co ban:           " << luongGoc << endl;
        double dieuChinh = luongCoBan - luongGoc;
        cout << "Dieu chinh ngay cong:   " << dieuChinh << endl;
        cout << "Luong CB thuc te:       " << luongCoBan << endl;
    } else if (loaiNV == "PartTime" || loaiNV == "Part-time") {
        cout << "Muc luong gio:          " << luongGoc << endl;
        cout << "Luong theo gio:         " << luongCoBan << endl;
    } else if (loaiNV == "ThucTap" || loaiNV == "Intern") {
        cout << "Muc tro cap/gio:        " << luongGoc << endl;
        cout << "Tien tro cap:           " << luongCoBan << endl;
    } else {
        cout << "Luong co ban:           " << luongCoBan << endl;
    }

    cout << "Phu cap:                " << phuCap << endl;
    cout << "Tien tang ca:           " << tienTangCa << endl;
    cout << "Khau tru:               " << -khauTru << endl;
    cout << string(40, '-') << endl;
    cout << ">> THUC NHAN:           " << luongThucNhan << endl;
    cout << "----------------------------------------" << endl;
}

string Luong::getMaLuong() const { return maLuong; }
string Luong::getMaNV() const { return maNV; }
string Luong::getLoaiNV() const { return loaiNV; }
int Luong::getThang() const { return thang; }
int Luong::getNam() const { return nam; }
double Luong::getLuongGoc() const { return luongGoc; }
double Luong::getLuongCoBan() const { return luongCoBan; }
double Luong::getPhuCap() const { return phuCap; }
double Luong::getTienTangCa() const { return tienTangCa; }
double Luong::getKhauTru() const { return khauTru; }
double Luong::getLuongThucNhan() const { return luongThucNhan; }

string Luong::taoDongDuLieu() const {
    return maLuong + "|" + maNV + "|" + loaiNV + "|" + to_string(thang) + "|" + to_string(nam) + "|" +
           to_string(luongGoc) + "|" + to_string(luongCoBan) + "|" +
           to_string(phuCap) + "|" + to_string(tienTangCa) + "|" +
           to_string(khauTru) + "|" + to_string(luongThucNhan);
}
