#include "QuanLyNhanVien.h"
#include "../models/NhanVienFullTime.h"
#include "../models/NhanVienPartTime.h"
#include "../models/NhanVienThucTap.h"
#include "../exceptions/Exceptions.h"
#include <iostream>
#include <algorithm>
#include <fstream>
#include <vector>
#include <sstream>

static std::vector<std::string> split(const std::string& s, char delimiter) {
    std::vector<std::string> tokens;
    std::string token;
    std::istringstream tokenStream(s);
    while (std::getline(tokenStream, token, delimiter)) {
        tokens.push_back(token);
    }
    return tokens;
}

bool QuanLyNhanVien::themNhanVien(std::unique_ptr<NhanVien> nv) {
    if (nv->getMaNV().empty()) throw InvalidInputException("Ma nhan vien khong duoc de trong");
    if (nv->getHoTen().empty()) throw InvalidInputException("Ho ten khong duoc de trong");

    // Yeu cau moi: Luong co ban phai lon hon 0 cho FullTime, cac loai khac co the bang 0 tuy nghiep vu
    // Nhung theo yeu cau chung cua user: Luong co ban > 0
    if (nv->getLuongCoBan() <= 0 && nv->getLoaiNV() == "FullTime") throw InvalidInputException("Luong co ban phai lon hon 0");

    if (timTheoMa(nv->getMaNV()) != nullptr) {
        throw DuplicateException("Ma nhan vien " + nv->getMaNV() + " da ton tai");
    }
    dsNhanVien.push_back(std::move(nv));
    return true;
}

void QuanLyNhanVien::hienThiDanhSach() const {
    if (dsNhanVien.empty()) {
        std::cout << "Danh sach nhan vien trong." << std::endl;
        return;
    }
    for (const auto& nv : dsNhanVien) {
        nv->hienThiThongTin();
    }
}

bool QuanLyNhanVien::suaNhanVien(std::string maNV) {
    NhanVien* nv = timTheoMa(maNV);
    if (!nv) throw NotFoundException("Khong tim thay nhan vien " + maNV);

    std::string ten;
    double luong;
    std::cout << "Nhap ten moi: ";
    std::getline(std::cin >> std::ws, ten);
    if (ten.empty()) throw InvalidInputException("Ho ten khong duoc de trong");

    std::cout << "Nhap luong co ban moi: ";
    if (!(std::cin >> luong)) {
        std::cin.clear();
        std::cin.ignore(1000, '\n');
        throw InvalidInputException("Phai nhap vao mot con so");
    }
    if (luong <= 0 && nv->getLoaiNV() == "FullTime") throw InvalidInputException("Luong co ban phai lon hon 0");

    nv->setHoTen(ten);
    nv->setLuongCoBan(luong);
    return true;
}

bool QuanLyNhanVien::xoaNhanVien(std::string maNV) {
    auto it = std::remove_if(dsNhanVien.begin(), dsNhanVien.end(),
        [&maNV](const std::unique_ptr<NhanVien>& nv) {
            return nv->getMaNV() == maNV;
        });

    if (it != dsNhanVien.end()) {
        dsNhanVien.erase(it, dsNhanVien.end());
        return true;
    }
    throw NotFoundException("Khong tim thay nhan vien " + maNV);
}

NhanVien* QuanLyNhanVien::timTheoMa(std::string maNV) const {
    for (const auto& nv : dsNhanVien) {
        if (nv->getMaNV() == maNV) return nv.get();
    }
    return nullptr;
}

std::vector<NhanVien*> QuanLyNhanVien::timTheoTen(std::string ten) const {
    std::vector<NhanVien*> ketQua;
    for (const auto& nv : dsNhanVien) {
        if (nv->getHoTen().find(ten) != std::string::npos) {
            ketQua.push_back(nv.get());
        }
    }
    return ketQua;
}

std::vector<NhanVien*> QuanLyNhanVien::timTheoPhongBan(std::string maPB) const {
    std::vector<NhanVien*> ketQua;
    for (const auto& nv : dsNhanVien) {
        if (nv->getMaPB() == maPB) {
            ketQua.push_back(nv.get());
        }
    }
    return ketQua;
}

std::vector<NhanVien*> QuanLyNhanVien::timTheoLoai(std::string loai) const {
    std::vector<NhanVien*> ketQua;
    for (const auto& nv : dsNhanVien) {
        if (nv->getLoaiNV() == loai) {
            ketQua.push_back(nv.get());
        }
    }
    return ketQua;
}

const std::vector<std::unique_ptr<NhanVien>>& QuanLyNhanVien::getDanhSach() const {
    return dsNhanVien;
}

int QuanLyNhanVien::getSoLuong() const {
    return dsNhanVien.size();
}

void QuanLyNhanVien::saveToFile(const std::string& filename) const {
    std::ofstream f(filename);
    if (f.is_open()) {
        for (const auto& nv : dsNhanVien) {
            f << nv->serialize() << std::endl;
        }
        f.close();
    }
}

void QuanLyNhanVien::loadFromFile(const std::string& filename) {
    std::ifstream f(filename);
    if (!f.is_open()) return;

    dsNhanVien.clear();
    std::string line;
    while (std::getline(f, line)) {
        try {
            if (line.empty()) continue;
            auto tokens = split(line, '|');
            if (tokens.size() < 11) continue;

            std::string ma = tokens[0];
            std::string ten = tokens[1];
            std::string ns = tokens[2];
            std::string gt = tokens[3];
            std::string sdt = tokens[4];
            std::string email = tokens[5];
            std::string dc = tokens[6];
            std::string mapb = tokens[7];
            std::string cv = tokens[8];
            std::string loai = tokens[9];
            double lcb = std::stod(tokens[10]);

            if (loai == "FullTime" && tokens.size() >= 12) {
                double pc = std::stod(tokens[11]);
                dsNhanVien.push_back(std::make_unique<NhanVienFullTime>(ma, ten, ns, gt, sdt, email, dc, mapb, cv, lcb, pc, 0));
            } else if (loai == "PartTime" && tokens.size() >= 12) {
                double ltg = std::stod(tokens[11]);
                dsNhanVien.push_back(std::make_unique<NhanVienPartTime>(ma, ten, ns, gt, sdt, email, dc, mapb, cv, lcb, ltg));
            } else if (loai == "ThucTap" && tokens.size() >= 12) {
                double tc = std::stod(tokens[11]);
                dsNhanVien.push_back(std::make_unique<NhanVienThucTap>(ma, ten, ns, gt, sdt, email, dc, mapb, cv, lcb, tc));
            }
        } catch (...) {
            // Khong crash neu du lieu file loi
            continue;
        }
    }
    f.close();
}
