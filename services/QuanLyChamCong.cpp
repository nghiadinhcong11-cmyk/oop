#include "QuanLyChamCong.h"
#include "../exceptions/Exceptions.h"
#include <iostream>
#include <algorithm>
#include <fstream>
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

void QuanLyChamCong::themChamCong(const ChamCong& cc) {
    if (cc.getMaCC().empty() || cc.getMaNV().empty()) throw InvalidInputException("Ma cham cong va ma nhan vien khong duoc de trong");
    if (cc.getThang() < 1 || cc.getThang() > 12) throw InvalidInputException("Thang phai tu 1 den 12");
    if (cc.getSoNgayCong() < 0) throw InvalidInputException("So ngay cong khong duoc am");
    if (cc.getSoNgayCong() > 31) throw InvalidInputException("So ngay cong phai tu 0 den 31");
    if (cc.getSoGioTangCa() < 0) throw InvalidInputException("So gio tang ca khong duoc am");
    if (!isfinite(cc.getSoNgayCong()) || !isfinite(cc.getSoGioTangCa())) {
        throw InvalidInputException("So ngay cong va so gio tang ca phai la so huu han");
    }

    if (timChamCong(cc.getMaNV(), cc.getThang(), cc.getNam()) == nullptr) {
        dsChamCong.push_back(cc);
    } else {
        throw DuplicateException("Nhan vien da co cham cong trong thang nay");
    }
}

void QuanLyChamCong::hienThiDanhSach() const {
    if (dsChamCong.empty()) {
        cout << "Danh sach cham cong trong." << endl;
        return;
    }
    cout << "\n--- DANH SACH CHAM CONG ---" << endl;
    cout << "Ma CC" << " | "
              << "Ma NV" << " | "
              << "Thang" << " | "
              << "Nam" << " | "
              << "So ngay cong" << " | "
              << "So gio tang ca" << endl;
    cout << string(90, '-') << endl;
    for (int i = 0; i < (dsChamCong.size()); i++) {
        cout << dsChamCong[i].getMaCC() << " | "
                  << dsChamCong[i].getMaNV() << " | "
                  << dsChamCong[i].getThang() << " | "
                  << dsChamCong[i].getNam() << " | "

                  << dsChamCong[i].getSoNgayCong() << " | "
                  << dsChamCong[i].getSoGioTangCa() << endl;
    }
}

ChamCong* QuanLyChamCong::timChamCong(string maNV, int thang, int nam) {
    for (int i = 0; i < (dsChamCong.size()); i++) {
        if (dsChamCong[i].getMaNV() == maNV &&
            dsChamCong[i].getThang() == thang &&
            dsChamCong[i].getNam() == nam) {
            return &dsChamCong[i];
        }
    }
    return nullptr;
}

bool QuanLyChamCong::suaChamCong(string maNV, int thang, int nam) {
    ChamCong* cc = timChamCong(maNV, thang, nam);
    if (!cc) throw NotFoundException("Khong tim thay cham cong cho NV " + maNV);

    double cong, tangca;
    cout << "Nhap so ngay cong moi: ";
    if (!(cin >> cong)) { cin.clear(); cin.ignore(1000, '\n'); throw InvalidInputException("Phai nhap so"); }
    if (cong < 0) throw InvalidInputException("So ngay cong khong duoc am");
    if (cong > 31) throw InvalidInputException("So ngay cong phai tu 0 den 31");

    cout << "Nhap so gio tang ca moi: ";
    if (!(cin >> tangca)) { cin.clear(); cin.ignore(1000, '\n'); throw InvalidInputException("Phai nhap so"); }
    if (tangca < 0) throw InvalidInputException("So gio tang ca khong duoc am");

    cc->setSoNgayCong(cong);
    cc->setSoGioTangCa(tangca);
    return true;
}

bool QuanLyChamCong::xoaChamCong(string maNV, int thang, int nam) {
    for (int i = 0; i < dsChamCong.size(); i++) {
        if (dsChamCong[i].getMaNV() == maNV &&
            dsChamCong[i].getThang() == thang &&
            dsChamCong[i].getNam() == nam) {
            dsChamCong.erase(dsChamCong.begin() + i);
            return true;
        }
    }
    throw NotFoundException("Khong tim thay cham cong de xoa");
}

vector<ChamCong*> QuanLyChamCong::timTheoNhanVien(string maNV) {
    vector<ChamCong*> kq;
    for (int i = 0; i < (dsChamCong.size()); i++) {
        if (dsChamCong[i].getMaNV() == maNV) kq.push_back(&dsChamCong[i]);
    }
    return kq;
}

vector<ChamCong*> QuanLyChamCong::timTheoThang(int thang, int nam) {
    vector<ChamCong*> kq;
    for (int i = 0; i < (dsChamCong.size()); i++) {
        if (dsChamCong[i].getThang() == thang && dsChamCong[i].getNam() == nam) {
            kq.push_back(&dsChamCong[i]);
        }
    }
    return kq;
}

void QuanLyChamCong::saveToFile(const string& filename) const {
    ofstream f(filename);
    if (!f.is_open()) {
        throw FileException("Khong the mo file de ghi: " + filename);
    }
    for (int i = 0; i < (dsChamCong.size()); i++) {
        f << dsChamCong[i].taoDongDuLieu() << endl;
        if (!f) throw FileException("Khong the ghi du lieu vao: " + filename);
    }
}

void QuanLyChamCong::loadFromFile(const string& filename) {
    ifstream f(filename);
    if (!f.is_open()) {
        throw FileException("Khong the mo file de doc: " + filename);
    }

    dsChamCong.clear();
    string line;
    int lineNumber = 0;
    while (getline(f, line)) {
        ++lineNumber;
        try {
            if (line.empty()) continue;
            vector<string> cacTruong = tachChuoi(line, '|');
            if (cacTruong.size() != 6) {
                throw DataFormatException(filename + ": dong " + to_string(lineNumber) + " phai co 6 truong");
            }
            ChamCong parsed(cacTruong[0], cacTruong[1], stoi(cacTruong[2]),
                            stoi(cacTruong[3]), stod(cacTruong[4]), stod(cacTruong[5]));
            themChamCong(parsed);
        } catch (const HRMSException&) {
            throw;
        } catch (const exception& e) {
            throw DataFormatException(filename + ": dong " + to_string(lineNumber) + " - " + layNoiDungLoi(e));
        }
    }
    f.close();
}
