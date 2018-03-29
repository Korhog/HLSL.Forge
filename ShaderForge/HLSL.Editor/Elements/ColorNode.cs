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

    public class ColorNode : HeaderRowContainerBase
    {
        public ColorNode(rMindBaseController parent) : base(parent)
        {
            AddRow(new rMindRow
            {
                InputNodeType = rMindNodeConnectionType.None,
                OutputNode = new Node(this)
                {
                    NodeValueFormat = NodeValueFormat.FLOAT4,
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
                    NodeValueFormat = NodeValueFormat.FLOAT4,
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
                    NodeValueFormat = NodeValueFormat.FLOAT4,
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
                    NodeValueFormat = NodeValueFormat.FLOAT4,
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
            Flyout fl = new Flyout
            {
                Placement = FlyoutPlacementMode.Bottom,
                Content = new FColor()                
            };

            fl.ShowAt(m_header_rect);           
        }

        public override string GetNodeValue(Node sender)
        {
            if (sender.IDS == "R") return "float4(1.0f, 0.0f, 0.0f, 1.0f)";
            if (sender.IDS == "G") return "float4(0.0f, 1.0f, 0.0f, 1.0f)";
            if (sender.IDS == "B") return "float4(0.0f, 0.0f, 1.0f, 1.0f)";
            if (sender.IDS == "A") return "float4(1.0f, 1.0f, 1.0f, 1.0f)";

            if (sender.IDS == "color")
                return "float4(1.0f, 1.0f, 1.0f, 1.0f)";

            return null;
        }
    }
}
