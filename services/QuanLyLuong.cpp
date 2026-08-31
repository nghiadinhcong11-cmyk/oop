#include "QuanLyLuong.h"
#include "../exceptions/Exceptions.h"
#include <iostream>
#include <fstream>
#include <sstream>

static std::vector<std::string> splitString(const std::string& s, char delimiter) {
    std::vector<std::string> tokens;
    std::string token;
    std::istringstream tokenStream(s);
    while (std::getline(tokenStream, token, delimiter)) {
        tokens.push_back(token);
    }
    return tokens;
}

void QuanLyLuong::themLuong(const Luong& l) {
    if (timLuong(l.getMaNV(), l.getThang(), l.getNam()) == nullptr) {
        dsLuong.push_back(l);
    } else {
        throw DuplicateException("Nhan vien da co bang luong trong thang nay");
    }
}

void QuanLyLuong::hienThiBangLuong(int thang, int nam) const {
    std::cout << "--- BANG LUONG THANG " << thang << "/" << nam << " ---" << std::endl;
    bool found = false;
    for (const auto& l : dsLuong) {
        if (l.getThang() == thang && l.getNam() == nam) {
            l.hienThiPhieuLuong();
            found = true;
        }
    }
    if (!found) std::cout << "Khong co du lieu." << std::endl;
}

void QuanLyLuong::hienThiTatCa() const {
    if (dsLuong.empty()) {
        std::cout << "Danh sach luong trong." << std::endl;
        return;
    }
    for (const auto& l : dsLuong) {
        l.hienThiPhieuLuong();
    }
}

Luong* QuanLyLuong::timLuong(std::string maNV, int thang, int nam) {
    for (auto& l : dsLuong) {
        if (l.getMaNV() == maNV && l.getThang() == thang && l.getNam() == nam) {
            return &l;
        }
    }
    return nullptr;
}

std::vector<Luong*> QuanLyLuong::timLuongTheoNhanVien(std::string maNV) {
    std::vector<Luong*> kq;
    for (auto& l : dsLuong) {
        if (l.getMaNV() == maNV) kq.push_back(&l);
    }
    return kq;
}

void QuanLyLuong::saveToFile(const std::string& filename) const {
    std::ofstream f(filename);
    if (f.is_open()) {
        for (const auto& l : dsLuong) {
            f << l.serialize() << std::endl;
        }
        f.close();
    }
}

void QuanLyLuong::loadFromFile(const std::string& filename) {
    std::ifstream f(filename);
    if (!f.is_open()) return;

    dsLuong.clear();
    std::string line;
    while (std::getline(f, line)) {
        try {
            if (line.empty()) continue;
            auto tokens = splitString(line, '|');
            if (tokens.size() >= 9) {
                dsLuong.push_back(Luong(tokens[0], tokens[1], std::stoi(tokens[2]), std::stoi(tokens[3]),
                                       std::stod(tokens[4]), std::stod(tokens[5]), std::stod(tokens[6]),
                                       std::stod(tokens[7]), std::stod(tokens[8])));
            }
        } catch (...) {
            continue;
        }
    }
    f.close();
}
