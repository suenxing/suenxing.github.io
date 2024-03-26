#include <stdio.h>
#include <string.h>

// 住房开放信息
typedef struct room
{
    char room_knum[10]; // 门牌号
    int room_status;    // 住房状态0代表空，1代表满
    char room_type[20]; // 住房类型
    int room_price;     // 住宿价格
} Room;

// 住宿信息
typedef struct hotel
{
    char hotel_name[20]; // 酒店名称
    int room_num;        // 酒店开放房间总数
    Room *rooms;         // Room 数组
} Hotel;

// 把当前酒店房间全部展示出来
void displayRooms(Hotel h)
{
    printf("当前酒店的住房信息如下:\n");
    for (int i = 0; i < h.room_num; i++)
    {
        printf("%s, %d, %s, %d\n", h.rooms[i].room_knum, h.rooms[i].room_status, h.rooms[i].room_type, h.rooms[i].room_price);
    }
    printf("酒店 %s 共有 %d 间房间\n", h.hotel_name, h.room_num);
}

// 预订指定住房
void bookingRoom(Hotel *h, char room_knum[])
{
    for (int i = 0; i < h->room_num; i++)
    {
        if (strcmp(h->rooms[i].room_knum, room_knum) == 0 && h->rooms[i].room_status == 0) // 如果门牌号和住房状态都符合
        {
            h->rooms[i].room_status = 1; // 把住房状态改为满
            printf("您已成功预订了 %s 号房\n", room_knum);
            return;
        }
    }
    printf("没有预订成功，请确认住房号\n");
}

// 取消指定住房
void cancelRoom(Hotel *h, char room_knum[])
{
    for (int i = 0; i < h->room_num; i++)
    {
        if (strcmp(h->rooms[i].room_knum, room_knum) == 0 && h->rooms[i].room_status == 1) // 如果门牌号和住房状态都符合
        {
            h->rooms[i].room_status = 0; // 把住房状态改为空
            printf("您已成功取消了 %s 号房\n", room_knum);
            return;
        }
    }
    printf("没有取消成功，请确认住房号\n");
}

int main()
{
    Hotel h = {
        .hotel_name = "南极洲酒店",
        .room_num = 6,
        .rooms =
            {
                {"101", 0, "单人间", 100},
                {"102", 1, "单人间", 100},
                {"201", 0, "标准双人间", 200},
                {"202", 0, "标准双人间", 200},
                {"301", 0, "大床房", 300},
                {"302", 0, "大床房", 300}}};

    // 调用各种函数
    displayRooms(h);        // 展示所有住房信息
    bookingRoom(&h, "301"); // 预订301号房间
    cancelRoom(&h, "202");  // 取消202号房间
    displayRooms(h);        // 再次展示所有住房信息

    return 0;
}
