using Windows.UI;
using Windows.UI.Xaml.Media;
using Windows.UI.Xaml;
using Windows.UI.Xaml.Controls;
using Windows.UI.Xaml.Controls.Primitives;
using HLSL.Controls.UI;

namespace HLSL.Elements
{
    using Base;

    using rMind.Elements;
    using rMind.Content.Row;
    using rMind.Nodes;
    using HLSL.Values;

    public class ColorNode : HeaderRowContainerBase
    {
        Flyout picker;
        decimal r = 0M;
        decimal g = 0M;
        decimal b = 0M;

        public ColorNode(rMindBaseController parent) : base(parent)
        {
            var cp = new ColorPicker();
            cp.ColorChanged += (s, e) => {
                r = e.NewColor.R / 255.0M;
                g = e.NewColor.G / 255.0M;
                b = e.NewColor.B / 255.0M;
            };
            
            picker = new Flyout
            {
                Placement = FlyoutPlacementMode.Bottom, 
                Content = cp
            };

            AddRow(new rMindRow
            {
                InputNodeType = rMindNodeConnectionType.None,
                OutputNode = new Node(this)
                {
                    HLSLValueBaseType = HLSLValueBaseType.FLOAT4,
                    UseAccentColor = false,
                    IDS = "color",
                    Label = "Color",
                    ConnectionType = rMindNodeConnectionType.Container,
                    NodeOrientation = rMindNodeOriantation.Right,
                    Stroke = new SolidColorBrush(Colors.White)
                }
            });

            AddSeparator();

            // Red
            AddRow(new rMindRow
            {
                InputNodeType = rMindNodeConnectionType.None,
                OutputNode = new Node(this)
                {
                    HLSLValueBaseType = HLSLValueBaseType.FLOAT,
                    HLSLValueSubType = HLSLValueSubType.X_R,
                    UseAccentColor = false,
                    IDS = "R",
                    Label = "R",
                    ConnectionType = rMindNodeConnectionType.Container,
                    NodeOrientation = rMindNodeOriantation.Right,
                    Stroke = new SolidColorBrush(Colors.IndianRed)
                }
            });

            // Green
            AddRow(new rMindRow
            {
                InputNodeType = rMindNodeConnectionType.None,
                OutputNode = new Node(this)
                {
                    HLSLValueBaseType = HLSLValueBaseType.FLOAT,
                    HLSLValueSubType = HLSLValueSubType.Y_G,
                    UseAccentColor = false,
                    IDS = "G",
                    Label = "G",
                    ConnectionType = rMindNodeConnectionType.Container,
                    NodeOrientation = rMindNodeOriantation.Right,
                    Stroke = new SolidColorBrush(Colors.Green)
                }
            });

            // Blue
            AddRow(new rMindRow
            {
                InputNodeType = rMindNodeConnectionType.None,
                OutputNode = new Node(this)
                {
                    HLSLValueBaseType = HLSLValueBaseType.FLOAT,
                    HLSLValueSubType = HLSLValueSubType.Z_B,
                    UseAccentColor = false,
                    IDS = "B",
                    Label = "B",
                    ConnectionType = rMindNodeConnectionType.Container,
                    NodeOrientation = rMindNodeOriantation.Right,
                    Stroke = new SolidColorBrush(Colors.DeepSkyBlue)
                }
            });
        }

        protected override void EditButtonClick(object sender, RoutedEventArgs args)
        {
            picker.ShowAt(m_header_rect);     
        }

        public override string GetNodeValue(Node sender)
        {
            string color = "1.0f";

            if (sender.IDS == "R") color = string.Format("{0:0.0#}f", r).Replace(',', '.');
            if (sender.IDS == "G") color = string.Format("{0:0.0#}f", g).Replace(',', '.');
            if (sender.IDS == "B") color = string.Format("{0:0.0#}f", b).Replace(',', '.');
            if (sender.IDS == "A") return "1.0f";

            if (sender.IDS == "color")
                return string.Format(
                    "float4({0}, {1}, {2}, 1.0f)",
                    string.Format("{0:0.0#}f", r).Replace(',', '.'),
                    string.Format("{0:0.0#}f", g).Replace(',', '.'),
                    string.Format("{0:0.0#}f", b).Replace(',', '.'));

            return color;
        }
    }
}
