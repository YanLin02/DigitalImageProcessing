#pragma once

#include <QtWidgets/QMainWindow>
#include <qlabel.h>

#include "ui_DigitallmageProcessing.h"
#include "numericselection.h"
#include "Image.h"

class DigitallmageProcessing : public QMainWindow
{
    Q_OBJECT
    
public:
    DigitallmageProcessing(QWidget *parent = nullptr);
    ~DigitallmageProcessing();
    
private slots:
    /// @brief 打开文件
    void on_actionOpenFile_triggered();
    /// @brief 灰度化
    void on_actionGray_triggered();
    /// @brief 增强
    void on_actionEnh_triggered();
    /// @brief 平移
    void on_actionTranslation_triggered();
    /// @brief 旋转
    void on_actionRotate_triggered();
    /// @brief 缩放
    void on_actionScale_triggered();
    /// @brief 傅里叶变换
    void on_actionFourier_triggered();
    /// @brief 直方图
    void on_actionShowHistogram_triggered();
    /// @brief 直方图均衡化
    void on_actionEqualization_triggered();
    
    void on_actionCleanImage_triggered();
    
    void on_actionCLAHE_triggered();
    //TODO 增加一个按钮使得输出可以保存、转化为输入
    //TODO 增加关闭按键
    
private:
    Ui::DigitallmageProcessingClass ui;///< UI

    QLabel* labelPath;///< 文件路径标签

    QLabel* originalImageLabel;///< 原始图像展示标签
    QLabel* processingImageLabel;///< 处理中图像展示标签(选用)
    QLabel* processedImageLabel;///< 处理后图像展示标签
    
    Image originalImage;///< 原始图像
    Image processingImage;///< 处理中图像(选用)
    Image processedImage;///< 处理后图像

    bool hasImage;///< 是否已经导入图像

    void cleanLabelImage();///< 清除图像标签
};
