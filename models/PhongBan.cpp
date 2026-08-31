#include "PhongBan.h"

PhongBan::PhongBan() {}

PhongBan::PhongBan(std::string maPB, std::string tenPB, std::string truongPhong, std::string moTa)
    : maPB(maPB), tenPB(tenPB), truongPhong(truongPhong), moTa(moTa) {}

std::string PhongBan::getMaPB() const { return maPB; }
std::string PhongBan::getTenPB() const { return tenPB; }

void PhongBan::setMaPB(std::string maPB) { this->maPB = maPB; }
void PhongBan::setTenPB(std::string tenPB) { this->tenPB = tenPB; }

void PhongBan::hienThi() const {
    std::cout << "Ma PB: " << maPB << " | Ten PB: " << tenPB
              << " | Truong Phong: " << truongPhong << std::endl;
}

std::string PhongBan::serialize() const {
    return maPB + "|" + tenPB + "|" + truongPhong + "|" + moTa;
}
