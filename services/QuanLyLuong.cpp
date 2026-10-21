#include "QuanLyLuong.h"
#include "../exceptions/Exceptions.h"
#include <iostream>
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

void QuanLyLuong::themLuong(const Luong& l) {
    if (l.getMaNV().empty()) throw InvalidInputException("Ma nhan vien trong bang luong khong duoc de trong");
    if (timLuong(l.getMaNV(), l.getThang(), l.getNam()) == nullptr) {
        dsLuong.push_back(l);
    } else {
        throw DuplicateException("Nhan vien da co bang luong trong thang nay");
    }
}

void QuanLyLuong::hienThiBangLuong(int thang, int nam) const {
    cout << "\n--- BANG LUONG THANG " << thang << "/" << nam << " ---" << endl;
    cout << "Ma Luong" << " | "
              << "Ma NV" << " | "
              << "Loai NV" << " | "
              << "Thang" << " | "
              << "Nam" << " | "
              << "Luong goc" << " | "
              << "Luong co ban" << " | "
              << "Phu cap" << " | "
              << "Tien tang ca" << " | "
              << "Khau tru" << " | "
              << "Luong thuc nhan" << endl;
    cout << string(177, '-') << endl;

    bool found = false;
    for (int i = 0; i < (dsLuong.size()); i++) {
        if (dsLuong[i].getThang() == thang && dsLuong[i].getNam() == nam) {
            cout << dsLuong[i].getMaLuong() << " | "
                      << dsLuong[i].getMaNV() << " | "
                      << dsLuong[i].getLoaiNV() << " | "
                      << dsLuong[i].getThang() << " | "
                      << dsLuong[i].getNam() << " | "

                      << dsLuong[i].getLuongGoc() << " | "
                      << dsLuong[i].getLuongCoBan() << " | "
                      << dsLuong[i].getPhuCap() << " | "
                      << dsLuong[i].getTienTangCa() << " | "
                      << dsLuong[i].getKhauTru() << " | "
                      << dsLuong[i].getLuongThucNhan() << endl;
            found = true;
        }
    }
    if (!found) cout << "Khong co du lieu cho thang nay." << endl;
}

void QuanLyLuong::hienThiTatCa() const {
    if (dsLuong.empty()) {
        cout << "Danh sach luong trong." << endl;
        return;
    }
    cout << "\n--- BANG LUONG TONG HOP ---" << endl;
    cout << "Ma Luong" << " | "
              << "Ma NV" << " | "
              << "Loai NV" << " | "
              << "Thang" << " | "
              << "Nam" << " | "
              << "Luong goc" << " | "
              << "Luong co ban" << " | "
              << "Phu cap" << " | "
              << "Tien tang ca" << " | "
              << "Khau tru" << " | "
              << "Luong thuc nhan" << endl;
    cout << string(177, '-') << endl;
    for (int i = 0; i < (dsLuong.size()); i++) {
        cout << dsLuong[i].getMaLuong() << " | "
                  << dsLuong[i].getMaNV() << " | "
                  << dsLuong[i].getLoaiNV() << " | "
                  << dsLuong[i].getThang() << " | "
                  << dsLuong[i].getNam() << " | "

                  << dsLuong[i].getLuongGoc() << " | "
                  << dsLuong[i].getLuongCoBan() << " | "
                  << dsLuong[i].getPhuCap() << " | "
                  << dsLuong[i].getTienTangCa() << " | "
                  << dsLuong[i].getKhauTru() << " | "
                  << dsLuong[i].getLuongThucNhan() << endl;
    }
}

Luong* QuanLyLuong::timLuong(string maNV, int thang, int nam) {
    for (int i = 0; i < (dsLuong.size()); i++) {
        if (dsLuong[i].getMaNV() == maNV &&
            dsLuong[i].getThang() == thang && dsLuong[i].getNam() == nam) {
            return &dsLuong[i];
        }
    }
    return nullptr;
}

vector<Luong*> QuanLyLuong::timLuongTheoNhanVien(string maNV) {
    vector<Luong*> kq;
    for (int i = 0; i < (dsLuong.size()); i++) {
        if (dsLuong[i].getMaNV() == maNV) kq.push_back(&dsLuong[i]);
    }
    return kq;
}

const vector<Luong>& QuanLyLuong::getDanhSach() const {
    return dsLuong;
}

void QuanLyLuong::saveToFile(const string& filename) const {
    ofstream f(filename);
    if (!f.is_open()) {
        throw FileException("Khong the mo file de ghi: " + filename);
    }
    for (int i = 0; i < (dsLuong.size()); i++) {
        f << dsLuong[i].taoDongDuLieu() << endl;
        if (!f) throw FileException("Khong the ghi du lieu vao: " + filename);
    }
}

void QuanLyLuong::loadFromFile(const string& filename) {
    ifstream f(filename);
    if (!f.is_open()) {
        throw FileException("Khong the mo file de doc: " + filename);
    }

    dsLuong.clear();
    string line;
    int lineNumber = 0;
    while (getline(f, line)) {
        ++lineNumber;
        try {
            if (line.empty()) continue;
            vector<string> cacTruong = tachChuoi(line, '|');
            if (cacTruong.size() >= 11) {
                if (cacTruong[2] != "Full-time" && cacTruong[2] != "Part-time" && cacTruong[2] != "Intern" &&
                    cacTruong[2] != "FullTime" && cacTruong[2] != "PartTime" && cacTruong[2] != "ThucTap") {
                    throw DataFormatException(filename + ": dong " + to_string(lineNumber) + " co loai nhan vien khong hop le");
                }
                dsLuong.push_back(Luong(cacTruong[0], cacTruong[1], cacTruong[2], stoi(cacTruong[3]), stoi(cacTruong[4]),
                                       stod(cacTruong[5]), stod(cacTruong[6]), stod(cacTruong[7]),
                                       stod(cacTruong[8]), stod(cacTruong[9]), stod(cacTruong[10])));
            } else if (cacTruong.size() == 10) {
                 dsLuong.push_back(Luong(cacTruong[0], cacTruong[1], "FullTime", stoi(cacTruong[2]), stoi(cacTruong[3]),
                                       stod(cacTruong[4]), stod(cacTruong[5]), stod(cacTruong[6]),
                                       stod(cacTruong[7]), stod(cacTruong[8]), stod(cacTruong[9])));
            } else if (cacTruong.size() == 9) {
                 dsLuong.push_back(Luong(cacTruong[0], cacTruong[1], "FullTime", stoi(cacTruong[2]), stoi(cacTruong[3]),
                                       stod(cacTruong[4]), stod(cacTruong[4]), stod(cacTruong[5]),
                                       stod(cacTruong[6]), stod(cacTruong[7]), stod(cacTruong[8])));
            } else {
                throw DataFormatException(filename + ": dong " + to_string(lineNumber) + " co so truong khong hop le");
            }
        } catch (const HRMSException&) {
            throw;
        } catch (const exception& e) {
            throw DataFormatException(filename + ": dong " + to_string(lineNumber) + " - " + layNoiDungLoi(e));
        }
    }
    f.close();
}
