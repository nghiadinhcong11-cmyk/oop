#include "QuanLyPhongBan.h"
#include "../exceptions/Exceptions.h"
#include <iostream>
#include <algorithm>
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
        std::cout << "Danh sach phong ban trong." << std::endl;
        return;
    }
    std::cout << "--- DANH SACH PHONG BAN ---" << std::endl;
    for (const auto& pb : dsPhongBan) {
        pb.hienThi();
    }
}

PhongBan* QuanLyPhongBan::timPhongBan(std::string maPB) {
    for (auto& pb : dsPhongBan) {
        if (pb.getMaPB() == maPB) return &pb;
    }
    return nullptr;
}

bool QuanLyPhongBan::suaPhongBan(std::string maPB) {
    PhongBan* pb = timPhongBan(maPB);
    if (!pb) throw NotFoundException("Khong tim thay phong ban " + maPB);

    std::string ten;
    std::cout << "Nhap ten phong ban moi: ";
    std::getline(std::cin >> std::ws, ten);
    if (ten.empty()) throw InvalidInputException("Ten phong ban khong duoc de trong");
    pb->setTenPB(ten);
    return true;
}

bool QuanLyPhongBan::xoaPhongBan(std::string maPB) {
    auto it = std::remove_if(dsPhongBan.begin(), dsPhongBan.end(),
        [&maPB](const PhongBan& pb) {
            return pb.getMaPB() == maPB;
        });

    if (it != dsPhongBan.end()) {
        dsPhongBan.erase(it, dsPhongBan.end());
        return true;
    }
    throw NotFoundException("Khong tim thay phong ban " + maPB);
}

const std::vector<PhongBan>& QuanLyPhongBan::getDanhSach() const {
    return dsPhongBan;
}

void QuanLyPhongBan::saveToFile(const std::string& filename) const {
    std::ofstream f(filename);
    if (f.is_open()) {
        for (const auto& pb : dsPhongBan) {
            f << pb.serialize() << std::endl;
        }
        f.close();
    }
}

void QuanLyPhongBan::loadFromFile(const std::string& filename) {
    std::ifstream f(filename);
    if (!f.is_open()) return;

    dsPhongBan.clear();
    std::string line;
    while (std::getline(f, line)) {
        try {
            if (line.empty()) continue;
            auto tokens = splitString(line, '|');
            if (tokens.size() >= 4) {
                dsPhongBan.push_back(PhongBan(tokens[0], tokens[1], tokens[2], tokens[3]));
            }
        } catch (...) {
            continue;
        }
    }
    f.close();
}
