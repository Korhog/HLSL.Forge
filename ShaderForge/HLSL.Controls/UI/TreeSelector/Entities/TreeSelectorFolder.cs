using System;
using System.Collections.Generic;
using System.Collections.ObjectModel;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace HLSL.Controls
{
    public class TreeSelectorFolder : ITreeSelectorItem
    {
        ObservableCollection<ITreeSelectorItem> children;
        public TreeSelectorFolder()
        {
            children = new ObservableCollection<ITreeSelectorItem>();
        }

        public string Name { get; set; }

        public bool Folder => true;

        public ITreeSelectorItem Parent { get; set; }

        public ObservableCollection<ITreeSelectorItem> Children => children;

        public ObservableCollection<TreeSelectorFolder> Folders { get; set; }

        public ObservableCollection<TreeSelectorItem> Items { get; set; }

        public void AddFolder(TreeSelectorFolder folder)
        {
            if (Folders == null)
                Folders = new ObservableCollection<TreeSelectorFolder>();
            Folders.Add(folder);

            var idx = Children.IndexOf(Children.Where(x => x is TreeSelectorFolder).LastOrDefault()) + 1;
            Children.Insert(idx, folder);
        }

        public void AddItem(TreeSelectorItem driver)
        {
            if (Items == null)
                Items = new ObservableCollection<TreeSelectorItem>();
            Items.Add(driver);
            Children.Add(driver);
        }

        public void Remove(ITreeSelectorItem item)
        {
            if (item is TreeSelectorItem)
            {
                Items.Remove(item as TreeSelectorItem);
                Children.Remove(item);
            }
            else if (item is TreeSelectorFolder)
            {
                Folders.Remove(item as TreeSelectorFolder);
                Children.Remove(item);
            }
        }
    }
}
