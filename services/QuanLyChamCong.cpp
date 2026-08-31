#include "QuanLyChamCong.h"
#include "../exceptions/Exceptions.h"
#include <iostream>
#include <algorithm>
#include <fstream>
#include <sstream>
#include <iomanip>

static std::vector<std::string> splitString(const std::string& s, char delimiter) {
    std::vector<std::string> tokens;
    size_t start = 0, end = 0;
    while ((end = s.find(delimiter, start)) != std::string::npos) {
        tokens.push_back(s.substr(start, end - start));
        start = end + 1;
    }
    tokens.push_back(s.substr(start));
    return tokens;
}

void QuanLyChamCong::themChamCong(const ChamCong& cc) {
    if (cc.getThang() < 1 || cc.getThang() > 12) throw InvalidInputException("Thang phai tu 1 den 12");
    if (cc.getSoNgayCong() < 0) throw InvalidInputException("So ngay cong khong duoc am");
    if (cc.getSoNgayCong() > 31) throw InvalidInputException("So ngay cong phai tu 0 den 31");
    if (cc.getSoGioTangCa() < 0) throw InvalidInputException("So gio tang ca khong duoc am");

    if (timChamCong(cc.getMaNV(), cc.getThang(), cc.getNam()) == nullptr) {
        dsChamCong.push_back(cc);
    } else {
        throw DuplicateException("Nhan vien da co cham cong trong thang nay");
    }
}

void QuanLyChamCong::hienThiDanhSach() const {
    if (dsChamCong.empty()) {
        std::cout << "Danh sach cham cong trong." << std::endl;
        return;
    }
    std::cout << "\n--- DANH SACH CHAM CONG ---" << std::endl;
    std::cout << std::left << std::setw(15) << "Ma NV"
              << std::setw(15) << "Thoi gian"
              << std::right << std::setw(12) << "Ngay cong"
              << std::setw(12) << "Tang ca (h)" << std::endl;
    std::cout << std::string(55, '-') << std::endl;
    for (const auto& cc : dsChamCong) {
        std::cout << std::left << std::setw(15) << cc.getMaNV()
                  << std::left << std::setw(15) << (std::to_string(cc.getThang()) + "/" + std::to_string(cc.getNam()))
                  << std::right << std::fixed << std::setprecision(2) << std::setw(12) << cc.getSoNgayCong()
                  << std::right << std::setw(12) << cc.getSoGioTangCa() << std::endl;
    }
}

ChamCong* QuanLyChamCong::timChamCong(std::string maNV, int thang, int nam) {
    for (auto& cc : dsChamCong) {
        if (cc.getMaNV() == maNV && cc.getThang() == thang && cc.getNam() == nam) {
            return &cc;
        }
    }
    return nullptr;
}

bool QuanLyChamCong::suaChamCong(std::string maNV, int thang, int nam) {
    ChamCong* cc = timChamCong(maNV, thang, nam);
    if (!cc) throw NotFoundException("Khong tim thay cham cong cho NV " + maNV);

    double cong, tangca;
    std::cout << "Nhap so ngay cong moi: ";
    if (!(std::cin >> cong)) { std::cin.clear(); std::cin.ignore(1000, '\n'); throw InvalidInputException("Phai nhap so"); }
    if (cong < 0) throw InvalidInputException("So ngay cong khong duoc am");
    if (cong > 31) throw InvalidInputException("So ngay cong phai tu 0 den 31");

    std::cout << "Nhap so gio tang ca moi: ";
    if (!(std::cin >> tangca)) { std::cin.clear(); std::cin.ignore(1000, '\n'); throw InvalidInputException("Phai nhap so"); }
    if (tangca < 0) throw InvalidInputException("So gio tang ca khong duoc am");

    cc->setSoNgayCong(cong);
    cc->setSoGioTangCa(tangca);
    return true;
}

bool QuanLyChamCong::xoaChamCong(std::string maNV, int thang, int nam) {
    auto it = std::remove_if(dsChamCong.begin(), dsChamCong.end(),
        [&](const ChamCong& cc) {
            return cc.getMaNV() == maNV && cc.getThang() == thang && cc.getNam() == nam;
        });

    if (it != dsChamCong.end()) {
        dsChamCong.erase(it, dsChamCong.end());
        return true;
    }
    throw NotFoundException("Khong tim thay cham cong de xoa");
}

std::vector<ChamCong*> QuanLyChamCong::timTheoNhanVien(std::string maNV) {
    std::vector<ChamCong*> kq;
    for (auto& cc : dsChamCong) {
        if (cc.getMaNV() == maNV) kq.push_back(&cc);
    }
    return kq;
}

std::vector<ChamCong*> QuanLyChamCong::timTheoThang(int thang, int nam) {
    std::vector<ChamCong*> kq;
    for (auto& cc : dsChamCong) {
        if (cc.getThang() == thang && cc.getNam() == nam) kq.push_back(&cc);
    }
    return kq;
}

void QuanLyChamCong::saveToFile(const std::string& filename) const {
    std::ofstream f(filename);
    if (f.is_open()) {
        for (const auto& cc : dsChamCong) {
            f << cc.serialize() << std::endl;
        }
        f.close();
    }
}

void QuanLyChamCong::loadFromFile(const std::string& filename) {
    std::ifstream f(filename);
    if (!f.is_open()) return;

    dsChamCong.clear();
    std::string line;
    while (std::getline(f, line)) {
        try {
            if (line.empty()) continue;
            auto tokens = splitString(line, '|');
            if (tokens.size() >= 6) {
                dsChamCong.push_back(ChamCong(tokens[0], tokens[1], std::stoi(tokens[2]),
                                              std::stoi(tokens[3]), std::stod(tokens[4]), std::stod(tokens[5])));
            }
        } catch (...) {
            continue;
        }
    }
    f.close();
}
