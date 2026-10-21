#ifndef HETHONGQLNS_H
#define HETHONGQLNS_H

#include "QuanLyNhanVien.h"
#include "QuanLyPhongBan.h"
#include "QuanLyChamCong.h"
#include "QuanLyLuong.h"

class HeThongQLNS {
private:
    QuanLyNhanVien qlnv;
    QuanLyPhongBan qlpb;
    QuanLyChamCong qlcc;
    QuanLyLuong qll;

public:
    void menuChinh();

    // Nhan vien
    void menuNhanVien();
    void themNhanVienMoi();

    // Phong ban
    void menuPhongBan();
    void themPhongBanMoi();

    // Cham cong
    void menuChamCong();
    void nhapChamCong();

    // Luong
    void menuLuong();
    void tinhLuong();
    void xemBangLuong();

    // Tim kiem & Thong ke
    void timKiem();
    void thongKe();

    void loadAll();
    void saveAll();
};

#endif // HETHONGQLNS_H
