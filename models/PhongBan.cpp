#include "PhongBan.h"
using namespace std;

PhongBan::PhongBan() {}

PhongBan::PhongBan(string maPB, string tenPB, string truongPhong, string moTa)
    : maPB(maPB), tenPB(tenPB), truongPhong(truongPhong), moTa(moTa) {}

string PhongBan::getMaPB() const { return maPB; }
string PhongBan::getTenPB() const { return tenPB; }

void PhongBan::setMaPB(string maPB) { this->maPB = maPB; }
void PhongBan::setTenPB(string tenPB) { this->tenPB = tenPB; }

void PhongBan::hienThi() const {
    cout << maPB
              << tenPB
              << truongPhong << endl;
}

string PhongBan::taoDongDuLieu() const {
    return maPB + "|" + tenPB + "|" + truongPhong + "|" + moTa;
}
