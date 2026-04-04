# 论文图表源文件说明 / Thesis Figures

本目录存放论文第4章各图的源文件（Mermaid 格式）及导出图像。  
This directory contains Mermaid source files and exported images for Chapter 4 figures.

---

## 文件列表 / Files

| 文件 | 对应论文图 | 说明 |
|------|-----------|------|
| `fig4-Y5-livemap-loop.mmd` | 图4‑Y5 | LiveMap 数据获取与绘制闭环图（简化版） |

---

## 如何渲染 / How to Render

### 方法 1 — GitHub 自动渲染
将 `.mmd` 文件内容直接粘贴到 Markdown 代码块中（以 ` ```mermaid ` 开头），  
推送到 GitHub 后即可在仓库页面内实时预览。

### 方法 2 — Mermaid CLI（推荐，生成 SVG/PNG）

```bash
# 安装 Mermaid CLI（需要 Node.js ≥ 18）
npm install -g @mermaid-js/mermaid-cli

# 导出为 SVG（无损，适合嵌入 LaTeX / Word）
mmdc -i fig4-Y5-livemap-loop.mmd -o fig4-Y5-livemap-loop.svg

# 导出为 PNG（300 dpi，适合插图）
mmdc -i fig4-Y5-livemap-loop.mmd -o fig4-Y5-livemap-loop.png --scale 3
```

### 方法 3 — Mermaid Live Editor（在线）
1. 访问 <https://mermaid.live/>  
2. 将 `.mmd` 文件内容粘贴到编辑器左侧  
3. 点击右上角 **Download SVG** 或 **Download PNG**

### 方法 4 — VS Code 插件
安装 **Mermaid Preview**（`bierner.markdown-mermaid`）插件后，  
在编辑器中打开 `.mmd` 文件即可实时预览，右键可导出图像。

---

## 论文引用说明 / Citation Note

正文引用建议使用如下句式（4.4.4 LiveMap 小节）：

> "LiveMap 的数据获取与绘制闭环如图4‑Y5所示，页面通过 Model 以 Pull/Subscribe  
> 从 GPS、SysConfig、TrackFilter 与 SportStatus 等节点获取快照或推送数据；  
> 坐标转换与瓦片计算分别由 MapConv 与 TileConv 完成，页面侧负责将转换结果  
> 映射到 LVGL 控件更新（瓦片、箭头与轨迹线）。"

---

## 箭头语义速查 / Arrow Semantics

| 标注 | 含义 |
|------|------|
| **Pull** | Model 按需获取节点当前快照（同步请求-响应） |
| **Subscribe** | Model 注册节点推送订阅（页面初始化时完成） |
| **Publish** | 节点主动向订阅方推送快照（SportStatus 节点侧行为） |
| **Notify** | 命令下发：单向控制指令（如设置 StatusBar 样式） |
| 虚线箭头 | 条件触发（如瓦片容器位置变化才触发 TrackReload） |
