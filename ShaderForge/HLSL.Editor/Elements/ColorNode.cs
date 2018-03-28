using Windows.UI;
using Windows.UI.Xaml.Media;
using Windows.UI.Xaml;
using Windows.UI.Xaml.Controls;
using Windows.UI.Xaml.Controls.Primitives;
using HLSL.Controls.UI;

namespace HLSL.Elements
{
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
                OutputNode = new rMindBaseNode(this)
                {
                    UseAccentColor = false,
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
                OutputNode = new rMindBaseNode(this)
                {
                    UseAccentColor = false,
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
                OutputNode = new rMindBaseNode(this)
                {
                    UseAccentColor = false,
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
                OutputNode = new rMindBaseNode(this)
                {
                    UseAccentColor = false,
                    Label = "B",
                    ConnectionType = rMindNodeConnectionType.Container,
                    NodeOrientation = rMindNodeOriantation.Right,
                    Stroke = new SolidColorBrush(Colors.DeepSkyBlue)
                }
            });
        }

        protected override void EditButtonClick(object sender, RoutedEventArgs args)
        { 
            /*
            Flyout fl = new Flyout
            {
                Placement = FlyoutPlacementMode.Bottom,
                Content = new FColor()                
            };

            fl.ShowAt(m_header_rect);   
            */
        }
    }
}
