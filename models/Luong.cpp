#include "Luong.h"
#include <iomanip>

Luong::Luong() : thang(1), nam(2024), luongCoBan(0), phuCap(0), tienTangCa(0), khauTru(0), luongThucNhan(0) {}

Luong::Luong(std::string maLuong, std::string maNV, int thang, int nam,
              double lcb, double pc, double ttc, double kt, double ltn)
    : maLuong(maLuong), maNV(maNV), thang(thang), nam(nam),
      luongCoBan(lcb), phuCap(pc), tienTangCa(ttc), khauTru(kt), luongThucNhan(ltn) {}

void Luong::hienThiPhieuLuong() const {
    std::cout << "--- PHIEU LUONG: " << maLuong << " ---" << std::endl;
    std::cout << "Ma NV: " << maNV << " | Thang: " << thang << "/" << nam << std::endl;
    std::cout << "Luong CB: " << std::fixed << std::setprecision(0) << luongCoBan << std::endl;
    std::cout << "Phu cap: " << phuCap << " | Tang ca: " << tienTangCa << std::endl;
    std::cout << "Khau tru: " << khauTru << std::endl;
    std::cout << ">> THUC NHAN: " << luongThucNhan << std::endl;
    std::cout << "---------------------------" << std::endl;
}

std::string Luong::getMaNV() const { return maNV; }
int Luong::getThang() const { return thang; }
int Luong::getNam() const { return nam; }

std::string Luong::serialize() const {
    return maLuong + "|" + maNV + "|" + std::to_string(thang) + "|" + std::to_string(nam) + "|" +
           std::to_string(luongCoBan) + "|" + std::to_string(phuCap) + "|" +
           std::to_string(tienTangCa) + "|" + std::to_string(khauTru) + "|" +
           std::to_string(luongThucNhan);
}
