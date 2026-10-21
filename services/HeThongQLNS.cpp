#include "HeThongQLNS.h"
#include "../models/NhanVienFullTime.h"
#include "../models/NhanVienPartTime.h"
#include "../models/NhanVienThucTap.h"
#include "../exceptions/Exceptions.h"
#include <iostream>
#include <map>

using namespace std;

const string FILE_NV = "data/nhanvien.txt";
const string FILE_PB = "data/phongban.txt";
const string FILE_CC = "data/chamcong.txt";
const string FILE_L = "data/luong.txt";

static int nhapSoNguyen() {
    int val;
    while (!(cin >> val)) {
        cin.clear();
        cin.ignore(1000, '\n');
        cout << "Loi: Vui long nhap mot con so. Nhap lai: ";
    }
    return val;
}

static double nhapSoThuc() {
    double val;
    while (!(cin >> val)) {
        cin.clear();
        cin.ignore(1000, '\n');
        cout << "Loi: Vui long nhap mot con so. Nhap lai: ";
    }
    return val;
}

void HeThongQLNS::loadAll() {
    cout << "Dang tai du lieu..." << endl;
    qlpb.loadFromFile(FILE_PB);
    qlnv.loadFromFile(FILE_NV);
    qlcc.loadFromFile(FILE_CC);
    qll.loadFromFile(FILE_L);
    cout << "Tai du lieu hoan tat." << endl;
}

void HeThongQLNS::saveAll() {
    qlpb.saveToFile(FILE_PB);
    qlnv.saveToFile(FILE_NV);
    qlcc.saveToFile(FILE_CC);
    qll.saveToFile(FILE_L);
}

void HeThongQLNS::menuChinh() {
    try {
        loadAll();
    } catch (const HRMSException& e) {
        cout << ">>> " << e.layNoiDungLoi() << endl;
        cout << "Chuong trinh tiep tuc voi du lieu dang trong." << endl;
    }
    int choice;
    do {
        try {
            cout << "\n==================================================" << endl;
            cout << "      HE THONG QUAN LY NHAN SU VA TIEN LUONG      " << endl;
            cout << "         CONG TY TNHH CONG NGHE SAO VIET          " << endl;
            cout << "==================================================" << endl;
            cout << "1. Quan ly nhan vien" << endl;
            cout << "2. Quan ly phong ban" << endl;
            cout << "3. Quan ly cham cong" << endl;
            cout << "4. Quan ly luong" << endl;
            cout << "5. Tim kiem nhan vien" << endl;
            cout << "6. Thong ke" << endl;
            cout << "0. Thoat" << endl;
            cout << "==================================================" << endl;
            cout << "Chon chuc nang: ";
            choice = nhapSoNguyen();

            switch (choice) {
                case 1: menuNhanVien(); break;
                case 2: menuPhongBan(); break;
                case 3: menuChamCong(); break;
                case 4: menuLuong(); break;
                case 5: timKiem(); break;
                case 6: thongKe(); break;
                case 0: cout << "Tam biet!" << endl; break;
                default: cout << "Loi: Lua chon khong hop le. Vui long chon lai" << endl;
            }
        } catch (const HRMSException& e) {
            cout << ">>> " << e.layNoiDungLoi() << endl;
        } catch (const exception& e) {
            cout << ">>> Loi he thong: " << layNoiDungLoi(e) << endl;
        }
    } while (choice != 0);
}

void HeThongQLNS::menuNhanVien() {
    int choice;
    do {
        cout << "\n==================================================" << endl;
        cout << "                QUAN LY NHAN VIEN                 " << endl;
        cout << "==================================================" << endl;
        cout << "1. Xem danh sach nhan vien" << endl;
        cout << "2. Them nhan vien moi" << endl;
        cout << "3. Sua thong tin nhan vien" << endl;
        cout << "4. Xoa nhan vien" << endl;
        cout << "5. Xem ho so chi tiet" << endl;
        cout << "0. Quay lai menu chinh" << endl;
        cout << "--------------------------------------------------" << endl;
        cout << "Chon: "; choice = nhapSoNguyen();

        try {
            if (choice == 1) qlnv.hienThiDanhSach();
            else if (choice == 2) {
                themNhanVienMoi();
                qlnv.saveToFile(FILE_NV);
                cout << ">>> Da them nhan vien!" << endl;
            }
            else if (choice == 3) {
                string ma; cout << "Nhap ma NV: "; cin >> ma;
                qlnv.suaNhanVien(ma);
                qlnv.saveToFile(FILE_NV);
                cout << ">>> Cap nhat thanh cong!" << endl;
            }
            else if (choice == 4) {
                string ma; cout << "Nhap ma NV: "; cin >> ma;
                qlnv.xoaNhanVien(ma);
                qlnv.saveToFile(FILE_NV);
                cout << ">>> Da xoa nhan vien!" << endl;
            }
            else if (choice == 5) {
                string ma; cout << "Nhap ma NV: "; cin >> ma;
                NhanVien* nv = qlnv.timTheoMa(ma);
                if (nv) nv->hienThiChiTiet();
                else throw NotFoundException("Khong tim thay nhan vien " + ma);
            }
            else if (choice != 0) {
                 cout << "Loi: Lua chon khong hop le." << endl;
            }
        } catch (const HRMSException& e) {
            cout << "\n[LOI]: " << e.layNoiDungLoi() << endl;
        }
    } while (choice != 0);
}

void HeThongQLNS::themNhanVienMoi() {
    string ma, ten, ns, gt, sdt, email, dc, mapb, cv, nvl;
    int loai;
    double lcb;

    cout << "Ma NV: "; cin >> ma;
    if (qlnv.timTheoMa(ma)) throw DuplicateException("Ma nhan vien " + ma + " da ton tai");

    cout << "Ho ten: "; getline(cin >> ws, ten);
    if (ten.empty()) throw InvalidInputException("Ho ten khong duoc de trong");

    cout << "Ngay sinh (yyyy-mm-dd): "; cin >> ns;
    cout << "Gioi tinh: "; cin >> gt;
    cout << "So dien thoai: "; cin >> sdt;
    cout << "Email: "; cin >> email;
    cout << "Dia chi: "; getline(cin >> ws, dc);
    cout << "Chuc vu: "; getline(cin >> ws, cv);
    cout << "Ngay vao lam (yyyy-mm-dd): "; cin >> nvl;

    cout << "Phong ban (maPB): "; cin >> mapb;
    if (!qlpb.timPhongBan(mapb)) throw NotFoundException("Khong tim thay phong ban " + mapb);

    cout << "Luong co ban (FT) hoac 0 (PT/Intern): "; lcb = nhapSoThuc();
    cout << "Loai (1:Full-time, 2:Part-time, 3:Intern): "; loai = nhapSoNguyen();

    unique_ptr<NhanVien> nv;
    if (loai == 1) {
        if (lcb <= 0) throw InvalidInputException("Luong co ban phai lon hon 0");
        double pc; cout << "Phu cap: "; pc = nhapSoThuc();
        nv = make_unique<NhanVienFullTime>(ma, ten, ns, gt, sdt, email, dc, mapb, cv, nvl, lcb, pc, 0);
    } else if (loai == 2) {
        double ltg; cout << "Luong theo gio: "; ltg = nhapSoThuc();
        nv = make_unique<NhanVienPartTime>(ma, ten, ns, gt, sdt, email, dc, mapb, cv, nvl, lcb, ltg);
    } else if (loai == 3) {
        double tc; cout << "Tro cap/gio: "; tc = nhapSoThuc();
        nv = make_unique<NhanVienThucTap>(ma, ten, ns, gt, sdt, email, dc, mapb, cv, nvl, lcb, tc);
    } else {
        throw InvalidInputException("Loai nhan vien khong hop le");
    }

    qlnv.themNhanVien(move(nv));
}

void HeThongQLNS::menuPhongBan() {
    int choice;
    do {
        cout << "\n==================================================" << endl;
        cout << "                QUAN LY PHONG BAN                 " << endl;
        cout << "==================================================" << endl;
        cout << "1. Xem danh sach phong ban" << endl;
        cout << "2. Them phong ban moi" << endl;
        cout << "3. Xoa phong ban" << endl;
        cout << "0. Quay lai menu chinh" << endl;
        cout << "--------------------------------------------------" << endl;
        cout << "Chon: "; choice = nhapSoNguyen();

        try {
            if (choice == 1) qlpb.hienThiDanhSach();
            else if (choice == 2) {
                themPhongBanMoi();
                qlpb.saveToFile(FILE_PB);
                cout << ">>> Da them phong ban!" << endl;
            }
            else if (choice == 3) {
                string ma; cout << "Nhap ma PB: "; cin >> ma;
                if (!qlpb.timPhongBan(ma)) throw NotFoundException("Khong tim thay phong ban " + ma);
                if (!qlnv.timTheoPhongBan(ma).empty()) {
                    throw InvalidInputException("Khong the xoa phong ban dang co nhan vien");
                }
                qlpb.xoaPhongBan(ma);
                qlpb.saveToFile(FILE_PB);
                cout << ">>> Da xoa phong ban!" << endl;
            }
            else if (choice != 0) {
                 cout << "Loi: Lua chon khong hop le." << endl;
            }
        } catch (const HRMSException& e) {
            cout << "\n[LOI]: " << e.layNoiDungLoi() << endl;
        }
    } while (choice != 0);
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
    do {
        cout << "\n==================================================" << endl;
        cout << "                QUAN LY CHAM CONG                 " << endl;
        cout << "==================================================" << endl;
        cout << "1. Xem lich su cham cong" << endl;
        cout << "2. Nhap cham cong moi" << endl;
        cout << "0. Quay lai menu chinh" << endl;
        cout << "--------------------------------------------------" << endl;
        cout << "Chon: "; choice = nhapSoNguyen();

        try {
            if (choice == 1) qlcc.hienThiDanhSach();
            else if (choice == 2) {
                nhapChamCong();
                qlcc.saveToFile(FILE_CC);
                cout << ">>> Ghi nhan cham cong thanh cong!" << endl;
            }
            else if (choice != 0) {
                 cout << "Loi: Lua chon khong hop le." << endl;
            }
        } catch (const HRMSException& e) {
            cout << "\n[LOI]: " << e.layNoiDungLoi() << endl;
        }
    } while (choice != 0);
}

void HeThongQLNS::nhapChamCong() {
    string maNV, maCC;
    int t, n;
    double snc, sgtc;
    cout << "Ma NV: "; cin >> maNV;
    if (!qlnv.timTheoMa(maNV)) throw NotFoundException("Khong tim thay nhan vien " + maNV);

    cout << "Thang: "; t = nhapSoNguyen();
    if (t < 1 || t > 12) throw InvalidInputException("Thang phai tu 1 den 12");

    cout << "Nam: "; n = nhapSoNguyen();

    cout << "So ngay cong: "; snc = nhapSoThuc();
    if (snc < 0) throw InvalidInputException("So ngay cong khong duoc am");
    if (snc > 31) throw InvalidInputException("So ngay cong phai tu 0 den 31");

    cout << "So gio tang ca: "; sgtc = nhapSoThuc();
    if (sgtc < 0) throw InvalidInputException("So gio tang ca khong duoc am");

    maCC = "CC_" + maNV + "_" + to_string(t) + "_" + to_string(n);
    qlcc.themChamCong(ChamCong(maCC, maNV, t, n, snc, sgtc));
    cout << "Da ghi nhan!" << endl;
}

void HeThongQLNS::menuLuong() {
    int choice;
    do {
        cout << "\n==================================================" << endl;
        cout << "                QUAN LY TIEN LUONG                " << endl;
        cout << "==================================================" << endl;
        cout << "1. Tinh luong nhan vien" << endl;
        cout << "2. Xem bang luong tong hop" << endl;
        cout << "3. Xem bang luong theo thang" << endl;
        cout << "0. Quay lai menu chinh" << endl;
        cout << "--------------------------------------------------" << endl;
        cout << "Chon: "; choice = nhapSoNguyen();

        try {
            if (choice == 1) tinhLuong();
            else if (choice == 2) qll.hienThiTatCa();
            else if (choice == 3) xemBangLuong();
            else if (choice != 0) cout << "Loi: Lua chon khong hop le." << endl;
        } catch (const HRMSException& e) {
            cout << "\n[LOI]: " << e.layNoiDungLoi() << endl;
        }
    } while (choice != 0);
}

void HeThongQLNS::xemBangLuong() {
    int t, n;
    cout << "Nhap thang: "; t = nhapSoNguyen();
    cout << "Nhap nam: "; n = nhapSoNguyen();
    qll.hienThiBangLuong(t, n);
}

void HeThongQLNS::tinhLuong() {
    try {
        string maNV;
        int t, n;
        cout << "Nhap ma NV: "; cin >> maNV;
        NhanVien* nv = qlnv.timTheoMa(maNV);
        if (!nv) throw NotFoundException("Khong tim thay nhan vien " + maNV);

        cout << "Thang: "; t = nhapSoNguyen();
        cout << "Nam: "; n = nhapSoNguyen();

        ChamCong* cc = qlcc.timChamCong(maNV, t, n);
        if (!cc) throw NotFoundException("Chua co cham cong cho NV " + maNV + " trong thang " + to_string(t));

        // Check duplicate Luong
        if (qll.timLuong(maNV, t, n)) throw DuplicateException("Nhan vien da co bang luong trong thang nay");

        double khauTru;
        cout << "Nhap khoan khau tru (bao hiem, thue, phat...): ";
        khauTru = nhapSoThuc();
        if (khauTru < 0) throw InvalidInputException("Khoan khau tru khong duoc am");

        double thucNhan = nv->tinhLuong(*cc) - khauTru;
        string maL = "L_" + maNV + "_" + to_string(t);
        Luong l(
            maL,
            maNV,
            nv->getLoaiNV(),
            t,
            n,
            nv->getLuongGoc(),
            nv->getLuongCoBan(*cc),
            nv->getPhuCap(),
            nv->getTienTangCa(*cc),
            khauTru,
            thucNhan
        );

        l.hienThiPhieuLuong();

        char save;
        cout << "Luu ket qua? (y/n): "; cin >> save;
        if (save == 'y') {
            qll.themLuong(l);
            qll.saveToFile(FILE_L);
            cout << "Da luu!" << endl;
        }
    } catch (const HRMSException& e) {
        cout << ">>> " << e.layNoiDungLoi() << endl;
    }
}

void HeThongQLNS::timKiem() {
    int choice;
    cout << "\n--- TIM KIEM ---" << endl;
    cout << "1. Theo ma" << endl;
    cout << "2. Theo ten (gan dung)" << endl;
    cout << "3. Theo phong ban" << endl;
    cout << "4. Theo loai nhan vien" << endl;
    cout << "Chon: "; choice = nhapSoNguyen();

    try {
        if (choice == 1) {
            string ma; cout << "Ma: "; cin >> ma;
            NhanVien* nv = qlnv.timTheoMa(ma);
            if (nv) nv->hienThiChiTiet();
            else throw NotFoundException("Khong tim thay nhan vien " + ma);
        } else if (choice == 2) {
            string ten; cout << "Ten: "; getline(cin >> ws, ten);
            vector<NhanVien*> ds = qlnv.timTheoTen(ten);
            if (ds.empty()) cout << "Khong co ket qua." << endl;
            for (int i = 0; i < (ds.size()); i++) {
                ds[i]->hienThiThongTin();
            }
        } else if (choice == 3) {
            string mapb; cout << "Ma PB: "; cin >> mapb;
            vector<NhanVien*> ds = qlnv.timTheoPhongBan(mapb);
            if (ds.empty()) cout << "Khong co ket qua." << endl;
            for (int i = 0; i < (ds.size()); i++) {
                ds[i]->hienThiThongTin();
            }
        } else if (choice == 4) {
            string loai; cout << "Loai (Full-time/Part-time/Intern): "; cin >> loai;
            vector<NhanVien*> ds = qlnv.timTheoLoai(loai);
            if (ds.empty()) cout << "Khong co ket qua." << endl;
            for (int i = 0; i < (ds.size()); i++) {
                ds[i]->hienThiThongTin();
            }
        }
        else {
             cout << "Loi: Lua chon khong hop le." << endl;
        }
    } catch (const HRMSException& e) {
        cout << ">>> " << e.layNoiDungLoi() << endl;
    }
}

void HeThongQLNS::thongKe() {
    cout << "\n--- THONG KE NHAN SU ---" << endl;
    int tongNV = qlnv.getSoLuong();
    cout << "Tong so nhan vien: " << tongNV << endl;

    map<string, int> count;
    count["Full-time"] = 0;
    count["Part-time"] = 0;
    count["Intern"] = 0;

    const vector<unique_ptr<NhanVien>>& danhSachNhanVien = qlnv.getDanhSach();
    for (int i = 0; i < (danhSachNhanVien.size()); i++) {
        count[danhSachNhanVien[i]->getLoaiNV()]++;
    }

    cout << "Full-time    : " << count["Full-time"] << endl;
    cout << "Part-time    : " << count["Part-time"] << endl;
    cout << "Intern       : " << count["Intern"] << endl;

    cout << "\n--- THONG KE THEO PHONG BAN ---" << endl;
    const vector<PhongBan>& danhSachPhongBan = qlpb.getDanhSach();
    for (int i = 0; i < (danhSachPhongBan.size()); i++) {
        vector<NhanVien*> ds = qlnv.timTheoPhongBan(danhSachPhongBan[i].getMaPB());
        cout << danhSachPhongBan[i].getTenPB()
             << ": " << ds.size() << " NV" << endl;
    }

    cout << "\n--- THONG KE LUONG ---" << endl;
    double tongQuyLuong = 0;
    double maxL = -1, minL = -1;
    int countL = 0;

    const vector<Luong>& danhSachLuong = qll.getDanhSach();
    for (int i = 0; i < (danhSachLuong.size()); i++) {
        tongQuyLuong += danhSachLuong[i].getLuongThucNhan();
        if (maxL == -1 || danhSachLuong[i].getLuongThucNhan() > maxL) {
            maxL = danhSachLuong[i].getLuongThucNhan();
        }
        if (minL == -1 || danhSachLuong[i].getLuongThucNhan() < minL) {
            minL = danhSachLuong[i].getLuongThucNhan();
        }
        countL++;
    }

    cout << "Tong quy luong chi tra: " << tongQuyLuong << endl;
    if (countL > 0) {
        cout << "Luong cao nhat        : " << maxL << endl;
        cout << "Luong thap nhat       : " << minL << endl;
        cout << "Luong trung binh      : " << tongQuyLuong / countL << endl;
    } else {
        cout << "Chua co du lieu luong." << endl;
    }
}
