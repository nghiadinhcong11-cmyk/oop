#include "HeThongQLNS.h"
#include "../models/NhanVienFullTime.h"
#include "../models/NhanVienPartTime.h"
#include "../models/NhanVienThucTap.h"
#include "../exceptions/Exceptions.h"
#include <iostream>
#include <iomanip>
#include <map>

using namespace std;

const string FILE_NV = "data/nhanvien.txt";
const string FILE_PB = "data/phongban.txt";
const string FILE_CC = "data/chamcong.txt";
const string FILE_L = "data/luong.txt";

static int getSafeInt() {
    int val;
    while (!(cin >> val)) {
        cin.clear();
        cin.ignore(1000, '\n');
        cout << "Loi: Vui long nhap mot con so. Nhap lai: ";
    }
    return val;
}

static double getSafeDouble() {
    double val;
    while (!(cin >> val)) {
        cin.clear();
        cin.ignore(1000, '\n');
        cout << "Loi: Vui long nhap mot con so. Nhap lai: ";
    }
    return val;
}

void HeThongQLNS::loadAll() {
    qlpb.loadFromFile(FILE_PB);
    qlnv.loadFromFile(FILE_NV);
    qlcc.loadFromFile(FILE_CC);
    qll.loadFromFile(FILE_L);
}

void HeThongQLNS::saveAll() {
    qlpb.saveToFile(FILE_PB);
    qlnv.saveToFile(FILE_NV);
    qlcc.saveToFile(FILE_CC);
    qll.saveToFile(FILE_L);
}

void HeThongQLNS::menuChinh() {
    loadAll();
    int choice;
    do {
        try {
            cout << "\n====================================" << endl;
            cout << "      HE THONG QUAN LY NHAN SU      " << endl;
            cout << "====================================" << endl;
            cout << "1. Quan ly nhan vien" << endl;
            cout << "2. Quan ly phong ban" << endl;
            cout << "3. Quan ly cham cong" << endl;
            cout << "4. Tinh luong" << endl;
            cout << "5. Tim kiem nhan vien" << endl;
            cout << "6. Thong ke" << endl;
            cout << "0. Thoat" << endl;
            cout << "Chon chuc nang: ";
            choice = getSafeInt();

            switch (choice) {
                case 1: menuNhanVien(); break;
                case 2: menuPhongBan(); break;
                case 3: menuChamCong(); break;
                case 4: tinhLuong(); break;
                case 5: timKiem(); break;
                case 6: thongKe(); break;
                case 0: cout << "Tam biet!" << endl; break;
                default: cout << "Loi: Lua chon khong hop le. Vui long chon lai" << endl;
            }
        } catch (const HRMSException& e) {
            cout << ">>> " << e.what() << endl;
        } catch (const exception& e) {
            cout << ">>> Loi he thong: " << e.what() << endl;
        }
    } while (choice != 0);
}

void HeThongQLNS::menuNhanVien() {
    int choice;
    cout << "\n--- QUAN LY NHAN VIEN ---" << endl;
    cout << "1. Xem danh sach" << endl;
    cout << "2. Them nhan vien" << endl;
    cout << "3. Sua nhan vien" << endl;
    cout << "4. Xoa nhan vien" << endl;
    cout << "Chon: "; choice = getSafeInt();

    try {
        if (choice == 1) qlnv.hienThiDanhSach();
        else if (choice == 2) {
            themNhanVienMoi();
            saveAll();
            cout << "Da them nhan vien!" << endl;
        }
        else if (choice == 3) {
            string ma; cout << "Nhap ma NV: "; cin >> ma;
            qlnv.suaNhanVien(ma);
            saveAll();
            cout << "Thanh cong!" << endl;
        }
        else if (choice == 4) {
            string ma; cout << "Nhap ma NV: "; cin >> ma;
            qlnv.xoaNhanVien(ma);
            saveAll();
            cout << "Da xoa!" << endl;
        }
        else {
             cout << "Loi: Lua chon khong hop le. Vui long chon lai" << endl;
        }
    } catch (const HRMSException& e) {
        cout << ">>> " << e.what() << endl;
    }
}

void HeThongQLNS::themNhanVienMoi() {
    string ma, ten, mapb;
    int loai;
    double lcb;

    cout << "Ma NV: "; cin >> ma;
    // Check duplication early for better UX, though Manager also checks
    if (qlnv.timTheoMa(ma)) throw DuplicateException("Ma nhan vien " + ma + " da ton tai");

    cout << "Ho ten: "; getline(cin >> ws, ten);
    if (ten.empty()) throw InvalidInputException("Ho ten khong duoc de trong");

    cout << "Phong ban (maPB): "; cin >> mapb;
    if (!qlpb.timPhongBan(mapb)) throw NotFoundException("Khong tim thay phong ban " + mapb);

    cout << "Luong co ban: "; lcb = getSafeDouble();
    cout << "Loai (1:FullTime, 2:PartTime, 3:ThucTap): "; loai = getSafeInt();

    unique_ptr<NhanVien> nv;
    if (loai == 1) {
        if (lcb <= 0) throw InvalidInputException("Luong co ban phai lon hon 0");
        double pc; cout << "Phu cap: "; pc = getSafeDouble();
        nv = make_unique<NhanVienFullTime>(ma, ten, "", "", "", "", "", mapb, "", lcb, pc, 0);
    } else if (loai == 2) {
        double ltg; cout << "Luong theo gio: "; ltg = getSafeDouble();
        nv = make_unique<NhanVienPartTime>(ma, ten, "", "", "", "", "", mapb, "", lcb, ltg);
    } else if (loai == 3) {
        double tc; cout << "Tro cap: "; tc = getSafeDouble();
        nv = make_unique<NhanVienThucTap>(ma, ten, "", "", "", "", "", mapb, "", lcb, tc);
    } else {
        throw InvalidInputException("Loai nhan vien khong hop le");
    }

    qlnv.themNhanVien(move(nv));
}

void HeThongQLNS::menuPhongBan() {
    int choice;
    cout << "\n--- QUAN LY PHONG BAN ---" << endl;
    cout << "1. Xem danh sach" << endl;
    cout << "2. Them phong ban" << endl;
    cout << "3. Xoa phong ban" << endl;
    cout << "Chon: "; choice = getSafeInt();

    try {
        if (choice == 1) qlpb.hienThiDanhSach();
        else if (choice == 2) {
            themPhongBanMoi();
            saveAll();
        }
        else if (choice == 3) {
            string ma; cout << "Nhap ma PB: "; cin >> ma;
            if (!qlpb.timPhongBan(ma)) throw NotFoundException("Khong tim thay phong ban " + ma);
            if (!qlnv.timTheoPhongBan(ma).empty()) {
                throw InvalidInputException("Khong the xoa phong ban dang co nhan vien");
            }
            qlpb.xoaPhongBan(ma);
            saveAll();
            cout << "Da xoa!" << endl;
        }
        else {
             cout << "Loi: Lua chon khong hop le. Vui long chon lai" << endl;
        }
    } catch (const HRMSException& e) {
        cout << ">>> " << e.what() << endl;
    }
}

void HeThongQLNS::themPhongBanMoi() {
    string ma, ten, tp;
    cout << "Ma PB: "; cin >> ma;
    if (qlpb.timPhongBan(ma)) throw DuplicateException("Ma phong ban " + ma + " da ton tai");

    cout << "Ten PB: "; getline(cin >> ws, ten);
    if (ten.empty()) throw InvalidInputException("Ten phong ban khong duoc de trong");

    cout << "Truong phong: "; getline(cin >> ws, tp);
    qlpb.themPhongBan(PhongBan(ma, ten, tp, ""));
    cout << "Da them phong ban!" << endl;
}

void HeThongQLNS::menuChamCong() {
    int choice;
    cout << "\n--- QUAN LY CHAM CONG ---" << endl;
    cout << "1. Xem danh sach" << endl;
    cout << "2. Nhap cham cong" << endl;
    cout << "Chon: "; choice = getSafeInt();
    try {
        if (choice == 1) qlcc.hienThiDanhSach();
        else if (choice == 2) {
            nhapChamCong();
            saveAll();
        }
        else {
             cout << "Loi: Lua chon khong hop le. Vui long chon lai" << endl;
        }
    } catch (const HRMSException& e) {
        cout << ">>> " << e.what() << endl;
    }
}

void HeThongQLNS::nhapChamCong() {
    string maNV, maCC;
    int t, n;
    double snc, sgtc;
    cout << "Ma NV: "; cin >> maNV;
    if (!qlnv.timTheoMa(maNV)) throw NotFoundException("Khong tim thay nhan vien " + maNV);

    cout << "Thang: "; t = getSafeInt();
    if (t < 1 || t > 12) throw InvalidInputException("Thang phai tu 1 den 12");

    cout << "Nam: "; n = getSafeInt();

    cout << "So ngay cong: "; snc = getSafeDouble();
    if (snc < 0) throw InvalidInputException("So ngay cong khong duoc am");
    if (snc > 31) throw InvalidInputException("So ngay cong phai tu 0 den 31");

    cout << "So gio tang ca: "; sgtc = getSafeDouble();
    if (sgtc < 0) throw InvalidInputException("So gio tang ca khong duoc am");

    maCC = "CC_" + maNV + "_" + to_string(t) + "_" + to_string(n);
    qlcc.themChamCong(ChamCong(maCC, maNV, t, n, snc, sgtc));
    cout << "Da ghi nhan!" << endl;
}

void HeThongQLNS::tinhLuong() {
    try {
        string maNV;
        int t, n;
        cout << "Nhap ma NV: "; cin >> maNV;
        NhanVien* nv = qlnv.timTheoMa(maNV);
        if (!nv) throw NotFoundException("Khong tim thay nhan vien " + maNV);

        cout << "Thang: "; t = getSafeInt();
        cout << "Nam: "; n = getSafeInt();

        ChamCong* cc = qlcc.timChamCong(maNV, t, n);
        if (!cc) throw NotFoundException("Chua co cham cong cho NV " + maNV + " trong thang " + to_string(t));

        // Check duplicate Luong
        if (qll.timLuong(maNV, t, n)) throw DuplicateException("Nhan vien da co bang luong trong thang nay");

        double thucNhan = nv->tinhLuong(*cc);
        string maL = "L_" + maNV + "_" + to_string(t);
        Luong l(maL, maNV, t, n, nv->getLuongCoBan(), nv->getPhuCap(), nv->getTienTangCa(*cc), 0, thucNhan);

        l.hienThiPhieuLuong();

        char save;
        cout << "Luu ket qua? (y/n): "; cin >> save;
        if (save == 'y') {
            qll.themLuong(l);
            saveAll();
            cout << "Da luu!" << endl;
        }
    } catch (const HRMSException& e) {
        cout << ">>> " << e.what() << endl;
    }
}

void HeThongQLNS::timKiem() {
    int choice;
    cout << "\n--- TIM KIEM ---" << endl;
    cout << "1. Theo ma" << endl;
    cout << "2. Theo ten" << endl;
    cout << "3. Theo phong ban" << endl;
    cout << "Chon: "; choice = getSafeInt();

    try {
        if (choice == 1) {
            string ma; cout << "Ma: "; cin >> ma;
            NhanVien* nv = qlnv.timTheoMa(ma);
            if (nv) nv->hienThiThongTin();
            else throw NotFoundException("Khong tim thay nhan vien " + ma);
        } else if (choice == 2) {
            string ten; cout << "Ten: "; getline(cin >> ws, ten);
            auto ds = qlnv.timTheoTen(ten);
            if (ds.empty()) cout << "Khong co ket qua." << endl;
            for (auto nv : ds) nv->hienThiThongTin();
        } else if (choice == 3) {
            string mapb; cout << "Ma PB: "; cin >> mapb;
            if (!qlpb.timPhongBan(mapb)) throw NotFoundException("Khong tim thay phong ban " + mapb);
            auto ds = qlnv.timTheoPhongBan(mapb);
            if (ds.empty()) cout << "Khong co ket qua." << endl;
            for (auto nv : ds) nv->hienThiThongTin();
        }
        else {
             cout << "Loi: Lua chon khong hop le. Vui long chon lai" << endl;
        }
    } catch (const HRMSException& e) {
        cout << ">>> " << e.what() << endl;
    }
}

void HeThongQLNS::thongKe() {
    cout << "\n--- THONG KE ---" << endl;
    int tongNV = qlnv.getSoLuong();
    cout << "Tong so NV: " << tongNV << endl;

    map<string, int> count;
    for (const auto& nv : qlnv.getDanhSach()) {
        count[nv->getLoaiNV()]++;
    }

    cout << "FullTime: " << count["FullTime"] << endl;
    cout << "PartTime: " << count["PartTime"] << endl;
    cout << "ThucTap: " << count["ThucTap"] << endl;

    cout << "\nTheo phong ban:" << endl;
    for (const auto& pb : qlpb.getDanhSach()) {
        auto ds = qlnv.timTheoPhongBan(pb.getMaPB());
        cout << pb.getTenPB() << ": " << ds.size() << " NV" << endl;
    }
}
