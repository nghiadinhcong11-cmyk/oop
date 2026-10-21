#include "QuanLyPhongBan.h"
#include "../exceptions/Exceptions.h"
#include <iostream>
#include <algorithm>
#include <fstream>

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

void QuanLyPhongBan::themPhongBan(const PhongBan& pb) {
    if (pb.getMaPB().empty()) throw InvalidInputException("Ma phong ban khong duoc de trong");
    if (pb.getTenPB().empty()) throw InvalidInputException("Ten phong ban khong duoc de trong");

    if (timPhongBan(pb.getMaPB()) == nullptr) {
        dsPhongBan.push_back(pb);
    } else {
        throw DuplicateException("Ma phong ban " + pb.getMaPB() + " da ton tai");
    }
}

void QuanLyPhongBan::hienThiDanhSach() const {
    if (dsPhongBan.empty()) {
        cout << "Danh sach phong ban trong." << endl;
        return;
    }
    cout << "\n--- DANH SACH PHONG BAN ---" << endl;
    cout << "Ma PB"
              << "Ten Phong Ban"
              << "Truong Phong" << endl;
    cout << string(55, '-') << endl;
    for (int i = 0; i < (dsPhongBan.size()); i++) {
        dsPhongBan[i].hienThi();
    }
}

PhongBan* QuanLyPhongBan::timPhongBan(string maPB) {
    for (int i = 0; i < (dsPhongBan.size()); i++) {
        if (dsPhongBan[i].getMaPB() == maPB) return &dsPhongBan[i];
    }
    return nullptr;
}

bool QuanLyPhongBan::suaPhongBan(string maPB) {
    PhongBan* pb = timPhongBan(maPB);
    if (!pb) throw NotFoundException("Khong tim thay phong ban " + maPB);

    string ten;
    cout << "Nhap ten phong ban moi: ";
    getline(cin >> ws, ten);
    if (ten.empty()) throw InvalidInputException("Ten phong ban khong duoc de trong");
    pb->setTenPB(ten);
    return true;
}

bool QuanLyPhongBan::xoaPhongBan(string maPB) {
    for (int i = 0; i < dsPhongBan.size(); i++) {
        if (dsPhongBan[i].getMaPB() == maPB) {
            dsPhongBan.erase(dsPhongBan.begin() + i);
            return true;
        }
    }
    throw NotFoundException("Khong tim thay phong ban " + maPB);
}

const vector<PhongBan>& QuanLyPhongBan::getDanhSach() const {
    return dsPhongBan;
}

void QuanLyPhongBan::saveToFile(const string& filename) const {
    ofstream f(filename);
    if (!f.is_open()) {
        throw FileException("Khong the mo file de ghi: " + filename);
    }
    for (int i = 0; i < (dsPhongBan.size()); i++) {
        f << dsPhongBan[i].taoDongDuLieu() << endl;
        if (!f) throw FileException("Khong the ghi du lieu vao: " + filename);
    }
}

void QuanLyPhongBan::loadFromFile(const string& filename) {
    ifstream f(filename);
    if (!f.is_open()) {
        throw FileException("Khong the mo file de doc: " + filename);
    }

    dsPhongBan.clear();
    string line;
    int lineNumber = 0;
    while (getline(f, line)) {
        ++lineNumber;
        try {
            if (line.empty()) continue;
            vector<string> cacTruong = tachChuoi(line, '|');
            if (cacTruong.size() != 4) {
                throw DataFormatException(filename + ": dong " + to_string(lineNumber) + " phai co 4 truong");
            }
            themPhongBan(PhongBan(cacTruong[0], cacTruong[1], cacTruong[2], cacTruong[3]));
        } catch (const HRMSException&) {
            throw;
        } catch (const exception& e) {
            throw DataFormatException(filename + ": dong " + to_string(lineNumber) + " - " + layNoiDungLoi(e));
        }
    }
    f.close();
}
