#include "QuanLyNhanVien.h"
#include "../models/NhanVienFullTime.h"
#include "../models/NhanVienPartTime.h"
#include "../models/NhanVienThucTap.h"
#include "../exceptions/Exceptions.h"
#include <iostream>
#include <algorithm>
#include <fstream>
#include <vector>
#include <cmath>

using namespace std;

static vector<string> tachChuoi(string dong, char kyTuNganCach) {
    vector<string> cacPhan;
    string phanHienTai = "";

    for (int i = 0; i < dong.length(); i++) {
        if (dong[i] == kyTuNganCach) {
            cacPhan.push_back(phanHienTai);
            phanHienTai = "";
        } else {
            phanHienTai += dong[i];
        }
    }

    cacPhan.push_back(phanHienTai);
    return cacPhan;
}

bool QuanLyNhanVien::themNhanVien(unique_ptr<NhanVien> nv) {
    if (nv->getMaNV().empty()) throw InvalidInputException("Ma nhan vien khong duoc de trong");
    if (nv->getHoTen().empty()) throw InvalidInputException("Ho ten khong duoc de trong");

    // getLuongGoc() là mức cấu hình đầu vào của từng loại nhân viên:
    // lương tháng Full-time, lương giờ Part-time hoặc trợ cấp giờ Intern.
    if (!isfinite(nv->getLuongGoc()) || nv->getLuongGoc() <= 0) {
        throw InvalidInputException("Muc luong hoac muc luong theo gio phai lon hon 0");
    }

    if (timTheoMa(nv->getMaNV()) != nullptr) {
        throw DuplicateException("Ma nhan vien " + nv->getMaNV() + " da ton tai");
    }
    dsNhanVien.push_back(move(nv));
    return true;
}

void QuanLyNhanVien::hienThiDanhSach() const {
    if (dsNhanVien.empty()) {
        cout << "Danh sach nhan vien trong." << endl;
        return;
    }
    cout << "\n--- DANH SACH NHAN VIEN ---" << endl;
    cout << "Ma NV" << " | "
              << "Ho ten" << " | "
              << "Ngay sinh" << " | "
              << "GT" << " | "
              << "So dien thoai" << " | "
              << "Email" << " | "
              << "Dia chi" << " | "
              << "Ma PB" << " | "
              << "Chuc vu" << " | "
              << "Ngay vao lam" << " | "
              << "Loai NV" << " | "
              << "Luong CB" << " | "
              << "Phu cap/L.Gio" << endl;
    cout << string(231, '-') << endl;
    for (int i = 0; i < (dsNhanVien.size()); i++) {
        dsNhanVien[i]->hienThiThongTin();
    }
}

bool QuanLyNhanVien::suaNhanVien(string maNV) {
    NhanVien* nv = timTheoMa(maNV);
    if (!nv) throw NotFoundException("Khong tim thay nhan vien " + maNV);

    string input;
    double luong;

    cout << "Nhap ho ten moi (Enter de giu nguyen): ";
    getline(cin >> ws, input);
    if (!input.empty()) nv->setHoTen(input);

    cout << "Nhap ngay sinh moi (dd/mm/yyyy - Enter de giu nguyen): ";
    getline(cin, input);
    if (!input.empty()) nv->setNgaySinh(input);

    cout << "Nhap gioi tinh moi (Enter de giu nguyen): ";
    getline(cin, input);
    if (!input.empty()) nv->setGioiTinh(input);

    cout << "Nhap SDT moi (Enter de giu nguyen): ";
    getline(cin, input);
    if (!input.empty()) nv->setSoDienThoai(input);

    cout << "Nhap Email moi (Enter de giu nguyen): ";
    getline(cin, input);
    if (!input.empty()) nv->setEmail(input);

    cout << "Nhap Dia chi moi (Enter de giu nguyen): ";
    getline(cin, input);
    if (!input.empty()) nv->setDiaChi(input);

    cout << "Nhap Chuc vu moi (Enter de giu nguyen): ";
    getline(cin, input);
    if (!input.empty()) nv->setChucVu(input);

    cout << "Nhap Ngay vao lam moi (yyyy-mm-dd - Enter de giu nguyen): ";
    getline(cin, input);
    if (!input.empty()) nv->setNgayVaoLam(input);

    cout << "Nhap ma Phong Ban moi (Enter de giu nguyen): ";
    getline(cin, input);
    if (!input.empty()) nv->setMaPB(input);

    cout << "Nhap luong co ban moi (Nhap 0 de giu nguyen): ";
    if (cin >> luong) {
        if (luong > 0) nv->setLuongCoBan(luong);
    } else {
        cin.clear();
        cin.ignore(1000, '\n');
    }

    return true;
}

bool QuanLyNhanVien::xoaNhanVien(string maNV) {
    for (int i = 0; i < dsNhanVien.size(); i++) {
        if (dsNhanVien[i]->getMaNV() == maNV) {
            dsNhanVien.erase(dsNhanVien.begin() + i);
            return true;
        }
    }
    throw NotFoundException("Khong tim thay nhan vien " + maNV);
}

NhanVien* QuanLyNhanVien::timTheoMa(string maNV) const {
    for (int i = 0; i < (dsNhanVien.size()); i++) {
        if (dsNhanVien[i]->getMaNV() == maNV) return dsNhanVien[i].get();
    }
    return nullptr;
}

vector<NhanVien*> QuanLyNhanVien::timTheoTen(string ten) const {
    vector<NhanVien*> ketQua;
    for (int i = 0; i < (dsNhanVien.size()); i++) {
        if (dsNhanVien[i]->getHoTen().find(ten) != string::npos) {
            ketQua.push_back(dsNhanVien[i].get());
        }
    }
    return ketQua;
}

vector<NhanVien*> QuanLyNhanVien::timTheoPhongBan(string maPB) const {
    vector<NhanVien*> ketQua;
    for (int i = 0; i < (dsNhanVien.size()); i++) {
        if (dsNhanVien[i]->getMaPB() == maPB) {
            ketQua.push_back(dsNhanVien[i].get());
        }
    }
    return ketQua;
}

vector<NhanVien*> QuanLyNhanVien::timTheoLoai(string loai) const {
    vector<NhanVien*> ketQua;
    for (int i = 0; i < (dsNhanVien.size()); i++) {
        if (dsNhanVien[i]->getLoaiNV() == loai) {
            ketQua.push_back(dsNhanVien[i].get());
        }
    }
    return ketQua;
}

const vector<unique_ptr<NhanVien>>& QuanLyNhanVien::getDanhSach() const {
    return dsNhanVien;
}

int QuanLyNhanVien::getSoLuong() const {
    return dsNhanVien.size();
}

void QuanLyNhanVien::saveToFile(const string& filename) const {
    ofstream f(filename);
    if (!f.is_open()) {
        throw FileException("Khong the mo file de ghi: " + filename);
    }
    for (int i = 0; i < (dsNhanVien.size()); i++) {
        f << dsNhanVien[i]->taoDongDuLieu() << endl;
        if (!f) throw FileException("Khong the ghi du lieu vao: " + filename);
    }
}

void QuanLyNhanVien::loadFromFile(const string& filename) {
    ifstream f(filename);
    if (!f.is_open()) {
        throw FileException("Khong the mo file de doc: " + filename);
    }

    dsNhanVien.clear();
    string line;
    int lineNumber = 0;
    while (getline(f, line)) {
        ++lineNumber;
        try {
            if (line.empty()) continue;
            vector<string> cacTruong = tachChuoi(line, '|');
            if (cacTruong.size() < 13) {
                throw DataFormatException(filename + ": dong " + to_string(lineNumber) + " thieu truong");
            }

            string ma = cacTruong[0];
            string ten = cacTruong[1];
            string ns = cacTruong[2];
            string gt = cacTruong[3];
            string sdt = cacTruong[4];
            string email = cacTruong[5];
            string dc = cacTruong[6];
            string mapb = cacTruong[7];
            string cv = cacTruong[8];
            string nvl = cacTruong[9];
            string loai = cacTruong[10];
            double lcb = stod(cacTruong[11]);
            unique_ptr<NhanVien> parsed;

            if (loai == "Full-time" && cacTruong.size() >= 13) {
                double pc = stod(cacTruong[12]);
                parsed = make_unique<NhanVienFullTime>(ma, ten, ns, gt, sdt, email, dc, mapb, cv, nvl, lcb, pc, 0);
            } else if (loai == "Part-time" && cacTruong.size() >= 13) {
                double ltg = stod(cacTruong[12]);
                parsed = make_unique<NhanVienPartTime>(ma, ten, ns, gt, sdt, email, dc, mapb, cv, nvl, lcb, ltg);
            } else if (loai == "Intern" && cacTruong.size() >= 13) {
                double tc = stod(cacTruong[12]);
                parsed = make_unique<NhanVienThucTap>(ma, ten, ns, gt, sdt, email, dc, mapb, cv, nvl, lcb, tc);
            } else {
                throw DataFormatException(filename + ": dong " + to_string(lineNumber) + " co loai nhan vien khong hop le");
            }
            themNhanVien(move(parsed));
        } catch (const HRMSException&) {
            throw;
        } catch (const exception& e) {
            throw DataFormatException(filename + ": dong loi - " + layNoiDungLoi(e));
        }
    }
    f.close();
}
