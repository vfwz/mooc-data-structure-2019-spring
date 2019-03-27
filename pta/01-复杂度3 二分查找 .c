Position BinarySearch(List L, ElementType X)
{
    int left = 1;
    int right = L -> Last;
    int mid;
    ElementType midElem;
    while(left <= right)
    {
        mid = (left + right)/2;
        midElem = L -> Data[mid];
        if(X == midElem)
        {
            return mid;
        }
        else if(X < midElem)
        {
            right = mid - 1;
        }
        else if(X > midElem)
        {
            left = mid + 1;
        }
    }
    return NotFound;
}
