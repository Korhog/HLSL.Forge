using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace HLSL.Elements
{
    using rMind.Elements;
    using rMind.Content.Row;
    using rMind.Nodes;
    using Windows.UI;
    using Windows.UI.Xaml.Media;

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
    }
}
