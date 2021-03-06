//
//  CustomTableView.h
//  CustomTable
//
//  Created by 孙昕 on 15/2/2.
//  Copyright (c) 2015年 孙昕. All rights reserved.
//

#import <UIKit/UIKit.h>
#import "LazyTableCellProtocol.h"
#import "LazyTableBaseSection.h"
@class LazyTableView;
typedef enum
{
    LazyTableTypeRequest,  //远程数据抓取的类型，使用reloadRequest
    LazyTableTypeManualStatic, //本地手工创建静态cell，需要addSection和reloadStatic结合使用
    LazyTableTypeArrayStatic,  //本地手工加载array的静态cell，需要addDataSource和reloadStatic结合使用
    LazyTableTypeBlockStatic   //本地手工使用block加载处理静态cell，需要addStaticCell和reloadStatic结合使用
}LazyTableType;
@protocol LazyTableViewDelegate<UITableViewDelegate,UITableViewDataSource>
/**
 *  即将开始远程抓取
 *
 *  @param tableview 当前的tableview
 *  @param bFirst    是否为初始加载还是加载更多
 */
-(void)LazyTableViewWillStartRequest:(LazyTableView*)tableview First:(BOOL)bFirst;
/**
 *  完成了远程抓取
 *
 *  @param tableview 当前的tableview
 *  @param dic       抓取到的dictionary类型数据
 *
 *  @return 返回一个array类型数据以供加载
 */
-(NSArray*)LazyTableViewDidFinishRequest:(LazyTableView*)tableview Request:(NSDictionary*)dic;
/**
 *  完成了加载
 *
 *  @param tableview 当前的tableview
 *  @param count     当前row的数量
 *  @param bFirst    是否为初始加载还是加载更多
 */
-(void)LazyTableViewDidFinishLoadData:(LazyTableView*)tableview Count:(NSInteger)count First:(BOOL)bFirst;
/**
 *  当加载出现错误时或者网络异常时
 *
 *  @param tableview 当前的tableview
 *  @param err       错误描述
 */
-(void)LazyTableViewLoadError:(LazyTableView*)tableview Error:(NSError*)err;
/**
 *  需要section时，通过dic的数据创建section并且返回
 *
 *  @param tableview 当前的tableview
 *  @param dic       抓取到的dictionary类型数据
 *
 *  @return 返回section
 */
-(LazyTableBaseSection*)LazyTableViewInfoForSection:(LazyTableView*)tableview Request:(NSDictionary*)dic;
@end
@interface LazyTableView : UITableView
/**
 *  注册cell和item，cell为自定义cell类的名称，item为绑定的数据的类
 *
 *  @param strCell cell为继承LazyTableCell的cell
 *  @param strItem item为继承LazyTableBaseItem的item
 */
-(void)registarCell:(NSString*)strCell StrItem:(NSString*)strItem;
/**
 *  设置分页字段的名称和起始数值
 *
 *  @param page      分页字段的名称
 *  @param indexPage 起始值
 */
-(void)setPageParam:(NSString*)page Page:(NSInteger)indexPage;
/**
 *  设置每页的数据的个数，如果设置了这个字段，则start=page，page变为起始位置，每次抓取按照start=start+count来抓取
 *
 *  @param countName  每页个数的字段名称
 *  @param countValue 每页个数的数值
 */
-(void)setCountParam:(NSString*)countName Count:(NSInteger)countValue;
/**
 *  抓取远程数据并加载，目前只支持get抓取
 *
 *  @param url url地址
 *  @param dic url的参数
 */
-(void)reloadRequest:(NSString*)url Param:(NSDictionary*)dic;
/**
 *  加载本地静态数据
 */
-(void)reloadStatic;
/**
 *  设置LazyTableView的delegate
 *
 *  @param delegate LazyTableView的delegate
 */
-(void)setDelegateAndDataSource:(id<LazyTableViewDelegate>)delegate;
/**
 *  添加一个section
 *
 *  @param section
 */
-(void)addSection:(LazyTableBaseSection*)section;
/**
 *  添加本地的静态array
 *
 *  @param arr
 */
-(void)addDataSource:(NSArray*)arr;
/**
 *  设置SectionIndexTitles
 *
 *  @param arr
 */
-(void)setSectionIndexTitles:(NSArray*)arr;
/**
 *  获取当前section的个数
 *
 *  @return section的个数
 */
-(NSInteger)getSectionCount;
/**
 *  获取当前row的个数
 *
 *  @return row的个数
 */
-(NSInteger)getRowCount;
/**
 *  当前网络抓取为一次性抓取全部数据，没有分页
 */
-(void)disablePage;
/**
 *  获取当前的DataSource
 *
 *  @return 当前的DataSource
 */
-(NSArray*)getDataSource;
/**
 *  获取当前远程抓取的url的参数
 *
 *  @return 远程抓取的url的参数
 */
-(NSMutableDictionary*)getParam;
/**
 *  添加静态cell，无需添加item，在registarCell时将item设为nil，采用block的方式，注意循环引用
 *
 *  @param height    cell的高度
 *  @param cellBlock cell内容的赋值
 *  @param cellClick cell点击的处理
 */
-(void)addStaticCell:(CGFloat)height  CellBlock:(void (^)(id cell))cellBlock ClickBlock:(void (^)(id cell))cellClick;
/**
 *  获取当前tableview的类型
 *
 *  @return tableview的类型
 */
-(LazyTableType)getTableType;
@end






