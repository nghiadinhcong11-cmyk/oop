#include "QuanLyLuong.h"
#include "../exceptions/Exceptions.h"
#include <iostream>
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

void QuanLyLuong::themLuong(const Luong& l) {
    if (timLuong(l.getMaNV(), l.getThang(), l.getNam()) == nullptr) {
        dsLuong.push_back(l);
    } else {
        throw DuplicateException("Nhan vien da co bang luong trong thang nay");
    }
}

void QuanLyLuong::hienThiBangLuong(int thang, int nam) const {
    std::cout << "\n--- BANG LUONG THANG " << thang << "/" << nam << " ---" << std::endl;
    std::cout << std::left << std::setw(10) << "Ma NV"
              << std::right << std::setw(12) << "Luong CB"
              << std::setw(12) << "Phu cap"
              << std::setw(12) << "Tang ca"
              << std::setw(15) << "THUC NHAN" << std::endl;
    std::cout << std::string(65, '-') << std::endl;

    bool found = false;
    for (const auto& l : dsLuong) {
        if (l.getThang() == thang && l.getNam() == nam) {
            std::cout << std::left << std::setw(10) << l.getMaNV()
                      << std::right << std::fixed << std::setprecision(2) << std::setw(12) << l.getLuongCoBan()
                      << std::right << std::setw(12) << l.getPhuCap()
                      << std::right << std::setw(12) << l.getTienTangCa()
                      << std::right << std::setw(15) << l.getLuongThucNhan() << std::endl;
            found = true;
        }
    }
    if (!found) std::cout << "Khong co du lieu cho thang nay." << std::endl;
}

void QuanLyLuong::hienThiTatCa() const {
    if (dsLuong.empty()) {
        std::cout << "Danh sach luong trong." << std::endl;
        return;
    }
    std::cout << "\n--- BANG LUONG TONG HOP ---" << std::endl;
    std::cout << std::left << std::setw(10) << "Ma NV"
              << std::setw(10) << "Thang"
              << std::right << std::setw(12) << "Luong CB"
              << std::setw(12) << "Phu cap"
              << std::setw(12) << "Tang ca"
              << std::setw(15) << "THUC NHAN" << std::endl;
    std::cout << std::string(75, '-') << std::endl;
    for (const auto& l : dsLuong) {
        std::cout << std::left << std::setw(10) << l.getMaNV()
                  << std::left << std::setw(10) << (std::to_string(l.getThang()) + "/" + std::to_string(l.getNam()))
                  << std::right << std::fixed << std::setprecision(2) << std::setw(12) << l.getLuongCoBan()
                  << std::right << std::setw(12) << l.getPhuCap()
                  << std::right << std::setw(12) << l.getTienTangCa()
                  << std::right << std::setw(15) << l.getLuongThucNhan() << std::endl;
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
